#include "rootmacro2rad.h"

void writeOutputFile(char histType, const char* histName, char *filename){
  
  FILE *out;
  char outFileName[256];
  strncpy(outFileName,filename,240);

  //radware file header info
  int32_t buffSize;
  char spLabel[8];
  int32_t arraySize;
  int32_t junk = 1;
  strncpy(spLabel,histName,8);

  switch (histType)
    {
      case 1:
        strncat(outFileName,".spe",16);
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
      case 1:
        buffSize = 24;
        arraySize = 4096;
        fwrite(&buffSize,sizeof(int32_t),1,out);
        fwrite(&spLabel,sizeof(spLabel),1,out);
        fwrite(&arraySize,sizeof(int32_t),1,out);
        fwrite(&junk,sizeof(int32_t),1,out);
        fwrite(&junk,sizeof(int32_t),1,out);
        fwrite(&junk,sizeof(int32_t),1,out);
        fwrite(&buffSize,sizeof(int32_t),1,out);

        int byteSize = arraySize*=4;
        fwrite(&byteSize,sizeof(int32_t),1,out);
        fwrite(&hist,byteSize,1,out);
        fwrite(&byteSize,sizeof(int32_t),1,out);
        break;
      default:
        break;
    }

}

int main(int argc, char *argv[])
{

  FILE *inp;
  char str[4096];
  char histName[256], outFileName[240];

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
  char histType = 0; //0=no hist, 1=TH1F
  int ind;
  float val;
  strncpy(histName,"",256);
  memset(hist,0,sizeof(hist));

  //setup output filename
  strncpy(str,argv[1],4096);
  tok = strtok(str,".");
  strncpy(outFileName,tok,240);

  //read the input file
  if(fgets(str,1024,inp)!=NULL)
    {
      tok = strtok (str," ");
      if(strncmp(tok,"void",256)!=0){
        printf("Input file %s does not appear to be a macro generated by ROOT.\n",argv[1]);
        exit(-1);
      }
      while((!feof(inp))&&(fgets(str,1024,inp))) //check for end of file and read next line
        {
          //printf("%s",str); //print the line
          tok = strtok (str," *->(),");
          if(histType>0){

            if(strncmp(tok,histName,256)==0){
               switch (histType)
                {
                  case 1:
                    //parse TH1F
                    tok = strtok (NULL," *->(),");
                    if(strncmp(tok,"SetBinContent",256)==0){
                      tok = strtok (NULL," *->(),");
                      ind=atoi(tok);
                      tok = strtok (NULL," *->(),");
                      val=atof(tok);
                      printf("Read bin %i with value %f\n",ind,val);
                      if((ind>=0)&&(ind<S32K)){
                        hist[ind]=val;
                      }
                    }
                    break;
                  default:
                    break;
                }
            }
          }
          
          if(strncmp(tok,"TH1F",256)==0){
            if(histType!=0){
              writeOutputFile(histType,histName,outFileName);
            }
            printf("1-D histogram (floating point) found.\n");
            histType = 1;
            tok = strtok (NULL," *");
            printf("Histogram name: %s\n",tok);
            strncpy(histName,tok,256);
          }
        }
    }
  else
    {
      printf("Specified file %s has nothing in it.\n",argv[1]);
      printf("Aborting...\n");
      exit(1);
    }

  writeOutputFile(histType,histName,outFileName);

  return(1); //great success
}
