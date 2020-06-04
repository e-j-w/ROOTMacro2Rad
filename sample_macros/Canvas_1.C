void Canvas_1()
{
//=========Macro generated from canvas: Canvas_1/Canvas_1
//=========  (Wed Jun  3 15:38:19 2020) by ROOT version 6.14/06
   TCanvas *Canvas_1 = new TCanvas("Canvas_1", "Canvas_1",2318,88,1518,866);
   Canvas_1->ToggleEventStatus();
   Canvas_1->SetHighLightColor(2);
   Canvas_1->Range(-525000,-60506.39,2725000,544557.4);
   Canvas_1->SetFillColor(0);
   Canvas_1->SetBorderMode(0);
   Canvas_1->SetBorderSize(2);
   Canvas_1->SetFrameBorderMode(0);
   Canvas_1->SetFrameBorderMode(0);
   
   TH1F *htemp__1 = new TH1F("htemp__1","TTigress.fHits.GetEnergy()",100,-200000,2400000);
   htemp__1->SetBinContent(8,461001);
   htemp__1->SetBinContent(9,438);
   htemp__1->SetBinContent(23,2);
   htemp__1->SetBinContent(71,1);
   htemp__1->SetBinContent(72,1);
   htemp__1->SetBinContent(87,1);
   htemp__1->SetBinContent(88,1);
   htemp__1->SetBinContent(92,1);
   htemp__1->SetBinContent(93,1);
   htemp__1->SetEntries(461447);
   htemp__1->SetDirectory(0);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("htemp");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 461447 ");
   ptstats_LaTex = ptstats->AddText("Mean  =  290.8");
   ptstats_LaTex = ptstats->AddText("Std Dev   =   7192");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   htemp__1->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(htemp__1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   htemp__1->SetLineColor(ci);
   htemp__1->GetXaxis()->SetTitle("TTigress.fHits.GetEnergy()");
   htemp__1->GetXaxis()->SetRange(1,100);
   htemp__1->GetXaxis()->SetLabelFont(42);
   htemp__1->GetXaxis()->SetLabelSize(0.035);
   htemp__1->GetXaxis()->SetTitleSize(0.035);
   htemp__1->GetXaxis()->SetTitleFont(42);
   htemp__1->GetYaxis()->SetLabelFont(42);
   htemp__1->GetYaxis()->SetLabelSize(0.035);
   htemp__1->GetYaxis()->SetTitleSize(0.035);
   htemp__1->GetYaxis()->SetTitleOffset(0);
   htemp__1->GetYaxis()->SetTitleFont(42);
   htemp__1->GetZaxis()->SetLabelFont(42);
   htemp__1->GetZaxis()->SetLabelSize(0.035);
   htemp__1->GetZaxis()->SetTitleSize(0.035);
   htemp__1->GetZaxis()->SetTitleFont(42);
   htemp__1->Draw("");
   
   TPaveText *pt = new TPaveText(0.3109103,0.9352844,0.6890897,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("TTigress.fHits.GetEnergy()");
   pt->Draw();
   Canvas_1->Modified();
   Canvas_1->cd();
   Canvas_1->SetSelected(Canvas_1);
}
