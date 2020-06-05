#include "rootmacro2rad.h"

void writeOutputFile(char histType, int histNum, const char* histName, char *filename){
  
  FILE *out;
  int i,j;
  float val;
  char outFileName[256], suffix[32];
  strncpy(outFileName,filename,224);

  //radware file header info
  int32_t buffSize;
  char spLabel[8];
  int32_t arraySize;
  int32_t junk = 1;
  strncpy(spLabel,histName,8);

  switch (histType)
    {
      case 2:
        snprintf(suffix,32,"hist%i.m4b",histNum);
        strncat(outFileName,suffix,32);
        break;
      case 1:
        snprintf(suffix,32,"hist%i.spe",histNum);
        strncat(outFileName,suffix,32);
        break;
      default:
        break;
    }

  if((out=fopen(outFileName,"w"))==NULL)
    {
      printf("\nOutput file %s is not accessible.\n",outFileName);
      exit(-1);
    }

  printf("Saving data to file: %s\n",outFileName);
  
  switch (histType)
    {
      case 2:
        for(i=0;i<S4K;i++){
          fwrite(hist2[i],sizeof(hist2[i]),1,out);
        }
        break;
      case 1:
        //write .spe header
        buffSize = 24;
        arraySize = S4K;
        fwrite(&buffSize,sizeof(int32_t),1,out);
        fwrite(&spLabel,sizeof(spLabel),1,out);
        fwrite(&arraySize,sizeof(int32_t),1,out);
        fwrite(&junk,sizeof(int32_t),1,out);
        fwrite(&junk,sizeof(int32_t),1,out);
        fwrite(&junk,sizeof(int32_t),1,out);
        fwrite(&buffSize,sizeof(int32_t),1,out);

        int byteSize = arraySize*=4;
        fwrite(&byteSize,sizeof(int32_t),1,out);
        for(i=0;i<S4K;i++){
          val = (float)hist[i];
          fwrite(&val,sizeof(float),1,out);
        }
        fwrite(&byteSize,sizeof(int32_t),1,out);
        break;
      default:
        break;
    }

  fclose(out);

  //write projection for a 2D histogram
  switch (histType)
    {
      case 2:
        strncpy(outFileName,filename,224);
        snprintf(suffix,32,"hist%i_proj.spe",histNum);
        strncat(outFileName,suffix,32);
        if((out=fopen(outFileName,"w"))==NULL)
          {
            printf("\nOutput file %s is not accessible.\n",outFileName);
            exit(-1);
          }
        printf("Saving projection data to file: %s\n",outFileName);
        
        //write .spe header
        buffSize = 24;
        arraySize = S4K;
        fwrite(&buffSize,sizeof(int32_t),1,out);
        fwrite(&spLabel,sizeof(spLabel),1,out);
        fwrite(&arraySize,sizeof(int32_t),1,out);
        fwrite(&junk,sizeof(int32_t),1,out);
        fwrite(&junk,sizeof(int32_t),1,out);
        fwrite(&junk,sizeof(int32_t),1,out);
        fwrite(&buffSize,sizeof(int32_t),1,out);

        int byteSize = arraySize*=4;
        fwrite(&byteSize,sizeof(int32_t),1,out);
        for(i=0;i<S4K;i++){
          val = 0.;
          for(j=0;j<S4K;j++)
            val += (float)hist2[j][i];
          //printf("projection index %i: %f\n",i,val);
          fwrite(&val,sizeof(float),1,out);
        }
        fwrite(&byteSize,sizeof(int32_t),1,out);
        break;
      default:
        break;
    }

}

int main(int argc, char *argv[])
{

  FILE *inp;
  char str[S4K];
  char histName[256], outFileName[224];

  if(argc!=2)
    {
      printf("rootmacro2rad macro_file\n");
      printf("\nConvert the specified ROOT macro (.C) file into something readable by RadWare.\nROOT macros can be generated using the 'File/Save' option in a ROOT TBrowser (select the .C file option).\n");
      exit(-1);
    }

  //read in command line arguments
  if((inp=fopen(argv[1],"r"))==NULL)
    {
        printf("\nSpecified file %s can not be opened\n",argv[1]);
        exit(-1);
    }

  char *tok;
  char histType = 0; //0=no hist, 1=TH1F,TH1D,TH1I
  int histNum=0;
  int ind, indx, indy;
  float val;
  int xsize=0;
  int ysize=0;
  strncpy(histName,"",256);
  memset(hist,0,sizeof(hist));
  memset(hist2,0,sizeof(hist2));

  //setup output filename
  strncpy(str,argv[1],S4K);
  tok = strtok(str,".");
  strncpy(outFileName,tok,224);

  //read the input file
  if(fgets(str,1024,inp)!=NULL)
    {
      while((!feof(inp))&&(fgets(str,1024,inp))) //check for end of file and read next line
        {
          //printf("%s",str); //print the line
          tok = strtok (str," *->(),");
          if(histType>0){

            if(strncmp(tok,histName,256)==0){
               switch (histType)
                {
                  case 2:
                    //parse TH2
                    tok = strtok (NULL," *->(),");
                    if(strncmp(tok,"SetBinContent",256)==0){
                      tok = strtok (NULL," *->(),");
                      ind=atoi(tok);
                      tok = strtok (NULL," *->(),");
                      val=atof(tok);
                      indx = ind % S4K;
                      indy = (int)floor(ind/(1.*S4K));
                      if((indx>=0)&&(indx<S4K)){
                        if((indy>=0)&&(indy<S4K)){
                          //printf("Read bin %i %i with value %f\n",indx,indy,val);
                          hist2[indx][indy]=val;
                        }
                      }
                    }
                    break;
                  case 1:
                    //parse TH1
                    tok = strtok (NULL," *->(),");
                    if(strncmp(tok,"SetBinContent",256)==0){
                      tok = strtok (NULL," *->(),");
                      ind=atoi(tok);
                      tok = strtok (NULL," *->(),");
                      val=atof(tok);
                      //printf("Read bin %i with value %f\n",ind,val);
                      if((ind>=0)&&(ind<S4K)){
                        hist[ind]=val;
                      }
                    }
                    break;
                  default:
                    break;
                }
            }
          }
          
          if((strncmp(tok,"TH1F",256)==0)||(strncmp(tok,"TH1D",256)==0)||(strncmp(tok,"TH1I",256)==0)){
            if(histType!=0){
              writeOutputFile(histType,histNum,histName,outFileName);
            }
            printf("1-D histogram found.\n");
            histType = 1;
            tok = strtok (NULL," *");
            printf("Histogram name: %s\n",tok);
            strncpy(histName,tok,256);
            histNum++;
          }else if((strncmp(tok,"TH2F",256)==0)||(strncmp(tok,"TH2D",256)==0)||(strncmp(tok,"TH2I",256)==0)){
            if(histType!=0){
              writeOutputFile(histType,histNum,histName,outFileName);
            }
            printf("2-D histogram found.\n");
            histType = 2;
            tok = strtok (NULL," *");
            printf("Histogram name: %s\n",tok);
            strncpy(histName,tok,256);
            tok = strtok (NULL,",");
            tok = strtok (NULL,",");
            tok = strtok (NULL,",");
            xsize = atoi(tok);
            tok = strtok (NULL,",");
            tok = strtok (NULL,",");
            tok = strtok (NULL,",");
            ysize = atoi(tok);
            printf("x size: %i, y size: %i\n",xsize,ysize);
            histNum++;
          }
        }
    }
  else
    {
      printf("Specified file %s has nothing in it.\n",argv[1]);
      printf("Aborting...\n");
      exit(1);
    }

  fclose(inp);

  if(histType > 0)
    writeOutputFile(histType,histNum,histName,outFileName);
  else
    printf("No compatible histogram types found, no data was saved.\n");
  printf("%i histogram(s) written.\n",histNum);

  return(1); //great success
}
