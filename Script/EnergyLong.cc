void EnergyLong()
{
    auto proton_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Proton_PowerLaw.root");
    auto proton_tree = (TTree*)proton_file->Get("B4");
    auto deuteron_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Deuteron_PowerLaw.root");
    auto deuteron_tree = (TTree*)deuteron_file->Get("B4");
    auto electron_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Electron_PowerLaw.root");
    auto electron_tree = (TTree*)electron_file->Get("B4");
    auto helium4_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Helium4_PowerLaw.root");
    auto helium4_tree = (TTree*)helium4_file->Get("B4");
    
    double Energy[19]={0};
    double Energy_LL[19]={0};
    double Energy_UL[19]={0};

    for (int i = 0; i < 1; i++) // Deposit Energy Bin
    {
        Energy[i]    =  1.2*i+0.1;
        Energy_LL[i] =  1.2*i;
        Energy_UL[i] =  1.2*i+0.2;

        TH1D *h1_p[14];  TF1  *fitFunc_p[14]; auto h2_p = new TH1D("h2_p","h2_p",14,0,14);  
        TH1D *h1_d[14];  TF1  *fitFunc_d[14]; auto h2_d = new TH1D("h2_d","h2_d",14,0,14);  
        TH1D *h1_e[14];  TF1  *fitFunc_e[14]; auto h2_e = new TH1D("h2_e","h2_e",14,0,14);  
        TH1D *h1_h[14];  TF1  *fitFunc_h[14]; auto h2_h = new TH1D("h2_h","h2_h",14,0,14);  

        TCut HET = Form("(L0_E+L1_E+L2_E>0.23) && (L3_E>0.046) && log10(Total_E)>%.2f && log10(Total_E)<=%.2f",Energy_LL[i],Energy_UL[i]);
        
        auto c1 = new TCanvas("c1","c1",2500,1500);
        c1->Clear();
        c1->Divide(5,3);
        gStyle->SetOptStat(0);

        auto c2 = new TCanvas("c2","c2",1200,1200);
        c2->Clear();
        gStyle->SetOptStat(0);

        for (int j= 0; j<15 ; j++) // Layer
        {

            if(j<=13) 
            {
                
                h1_p[j] = new TH1D(Form("h1_p[%d]",j), Form("h1_p[%d]",j),50,-5,0);  
                h1_d[j] = new TH1D(Form("h1_d[%d]",j), Form("h1_d[%d]",j),50,-5,0);  
                h1_e[j] = new TH1D(Form("h1_e[%d]",j), Form("h1_e[%d]",j),50,-5,0);  
                h1_h[j] = new TH1D(Form("h1_h[%d]",j), Form("h1_h[%d]",j),50,-5,0);  

                proton_tree->Draw(Form("log10(L%d_E/Total_E)>>h1_p[%d]",j,j),HET,"");   h1_p[j]->Scale(1.0/h1_p[j]->Integral());h1_p[j]->SetLineColor(kRed);     h1_p[j]->SetMarkerColor(kRed);     h1_p[j]->SetLineWidth(2);h1_p[j]->GetYaxis()->SetRangeUser(0,0.25);h1_p[j]->SetTitle(Form("EdepRatio Distrubution in L%d;log_{10}(Energy Deposit Ratio);Normalized Count",j));
                deuteron_tree->Draw(Form("log10(L%d_E/Total_E)>>h1_d[%d]",j,j),HET,""); h1_d[j]->Scale(1.0/h1_d[j]->Integral());h1_d[j]->SetLineColor(kBlue);    h1_d[j]->SetMarkerColor(kBlue);    h1_d[j]->SetLineWidth(2);
                electron_tree->Draw(Form("log10(L%d_E/Total_E)>>h1_e[%d]",j,j),HET,""); h1_e[j]->Scale(1.0/h1_e[j]->Integral());h1_e[j]->SetLineColor(kOrange-3);h1_e[j]->SetMarkerColor(kOrange-3);h1_e[j]->SetLineWidth(2);
                helium4_tree->Draw(Form("log10(L%d_E/Total_E)>>h1_h[%d]",j,j),HET,"");  h1_h[j]->Scale(1.0/h1_h[j]->Integral());h1_h[j]->SetLineColor(kGreen-3); h1_h[j]->SetMarkerColor(kGreen-3); h1_h[j]->SetLineWidth(2);
                
                c1->cd(j + 1);
                h1_p[j]->Draw();
                h1_d[j]->Draw("same");
                h1_e[j]->Draw("same");
                h1_h[j]->Draw("same");

                h2_p->SetBinContent(j+1,h1_p[j]->GetMean() );
                h2_p->SetBinError  (j+1,h1_p[j]->GetRMS() );
                h2_d->SetBinContent(j+1,h1_d[j]->GetMean() );
                h2_d->SetBinError  (j+1,h1_d[j]->GetRMS() );
                h2_e->SetBinContent(j+1,h1_e[j]->GetMean() );
                h2_e->SetBinError  (j+1,h1_e[j]->GetRMS() );
                h2_h->SetBinContent(j+1,h1_h[j]->GetMean() );
                h2_h->SetBinError  (j+1,h1_h[j]->GetRMS() );
            }
            else // (j==14)    
            {
                c1->cd(j + 1);
                TLatex *tex = new TLatex(0.1,0.9,Form("IncidentParicle %dGeV",int(Energy[i])));tex->SetNDC();tex->Draw(); 
                auto legend1 = new TLegend(0.12, 0.12, 0.88, 0.88);
                legend1->AddEntry(h1_p[i], "Proton", "l");
                legend1->AddEntry(h1_d[i], "Deuteron", "l");
                legend1->AddEntry(h1_e[i], "Electron", "l");
                legend1->AddEntry(h1_h[i], "Helium4", "l");         
                legend1->Draw();       
            }
        }
        c2->cd();
        h2_p->SetTitle(Form("E_{dep}/GeV in [%.2f,%.2f];No. BGO Layer;Energy Ratio",Energy_LL[i],Energy_UL[i]));
        h2_p->SetLineColor(kRed);     h2_p->SetMarkerColor(kRed);     h2_p->SetLineWidth(2);
        h2_d->SetLineColor(kBlue);    h2_d->SetMarkerColor(kBlue);    h2_d->SetLineWidth(2);
        h2_e->SetLineColor(kOrange-3);h2_e->SetMarkerColor(kOrange-3);h2_e->SetLineWidth(2);
        h2_h->SetLineColor(kGreen-3); h2_h->SetMarkerColor(kGreen-3); h2_h->SetLineWidth(2);
        h2_p->Draw();
        h2_d->Draw("same");
        h2_e->Draw("same");
        h2_h->Draw("same");

        auto legend2 = new TLegend(0.72, 0.72, 0.88, 0.88);
        legend2->AddEntry(h2_p, "Proton", "l");
        legend2->AddEntry(h2_d, "Deuteron", "l");
        legend2->AddEntry(h2_e, "Electron", "l");
        legend2->AddEntry(h2_h, "Helium4", "l");         
        legend2->Draw();       

    }
}
