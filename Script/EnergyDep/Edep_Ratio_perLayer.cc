void Edep_Ratio_perLayer()
{
    double Energy[19]={0};
    for (int i = 0; i < 19; i++) // Energy
    {
        if(i<9)  {Energy[i] =  (i+1)*10;}
        else   {Energy[i] =  i*100-800;}

        TCut UBT = "L0_E+L1_E>0.0092";
        TCut HET = "(L0_E+L1_E+L2_E>0.23) && (L3_E>0.046)";
        TH1D *h1_p[14];  TF1  *fitFunc_p[14];
        TH1D *h1_d[14];  TF1  *fitFunc_d[14];
        TH1D *h1_e[14];  TF1  *fitFunc_e[14];
        TH1D *h1_h[14];  TF1  *fitFunc_h[14];

        double Proton_Ratio[14]={0};     double Deuteron_Ratio[14]={0};    double Electron_Ratio[14]={0};    double Helium4_Ratio[14]={0};   
        double Proton_Ratio_LL[14]={0};  double Deuteron_Ratio_LL[14]={0}; double Electron_Ratio_LL[14]={0}; double Helium4_Ratio_LL[14]={0};   
        double Proton_Ratio_UL[14]={0};  double Deuteron_Ratio_UL[14]={0}; double Electron_Ratio_UL[14]={0}; double Helium4_Ratio_UL[14]={0};   

        double Layer[14]={0};
        double Layer_Err[14]={0};

        auto proton_file = TFile::Open(Form("/Users/xiongzheng/software/B4/B4c/Root/Proton_%dGeV.root",int(Energy[i])));
        auto proton_tree = (TTree*)proton_file->Get("B4");
        auto deuteron_file = TFile::Open(Form("/Users/xiongzheng/software/B4/B4c/Root/Deuteron_%dGeV.root",int(Energy[i])));
        auto deuteron_tree = (TTree*)deuteron_file->Get("B4");
        auto electron_file = TFile::Open(Form("/Users/xiongzheng/software/B4/B4c/Root/Electron_%dGeV.root",int(Energy[i])));
        auto electron_tree = (TTree*)electron_file->Get("B4");
        auto helium4_file = TFile::Open(Form("/Users/xiongzheng/software/B4/B4c/Root/Helium4_%dGeV.root",int(Energy[i])));
        auto helium4_tree = (TTree*)helium4_file->Get("B4");

        auto c1 = new TCanvas("c1","c1",2500,1500);
        c1->Clear();
        c1->Divide(5,3);
        gStyle->SetOptStat(0);

        for (int j = 0; j < 15; j++) // Sub Fig
        {            
            c1->cd(j + 1);
            if(j<=13)
            {
                h1_p[j] = new TH1D(Form("h1_p[%d]",j), Form("h1_p[%d]",j),50,-5,0);  
                h1_d[j] = new TH1D(Form("h1_d[%d]",j), Form("h1_d[%d]",j),50,-5,0);  
                h1_e[j] = new TH1D(Form("h1_e[%d]",j), Form("h1_e[%d]",j),50,-5,0);  
                h1_h[j] = new TH1D(Form("h1_h[%d]",j), Form("h1_h[%d]",j),50,-5,0);  
                fitFunc_p[i] = new TF1(Form("fitFunc_p[%d]",i),"[0]/(-x*[2]*TMath::Sqrt(2*TMath::Pi()))*TMath::Exp(-0.5*TMath::Power(TMath::Log10(-x)-[1],2)/TMath::Power([2],2))", -4, 0); 
                fitFunc_p[i]->SetParameters(1, 0, 0.25); // Example values for the parameters
                
                proton_tree->Draw(Form("log10(L%d_E/Total_E)>>h1_p[%d]",j,j),HET,"");   h1_p[j]->Scale(1.0/h1_p[j]->Integral());h1_p[j]->SetLineColor(kRed);     h1_p[j]->SetMarkerColor(kRed);     h1_p[j]->SetLineWidth(2);h1_p[j]->GetYaxis()->SetRangeUser(0,0.25);h1_p[j]->SetTitle(Form("EdepRatio Distrubution in L%d;log_{10}(Energy Deposit Ratio);Normalized Count",j));
                deuteron_tree->Draw(Form("log10(L%d_E/Total_E)>>h1_d[%d]",j,j),HET,""); h1_d[j]->Scale(1.0/h1_d[j]->Integral());h1_d[j]->SetLineColor(kBlue);    h1_d[j]->SetMarkerColor(kBlue);    h1_d[j]->SetLineWidth(2);
                electron_tree->Draw(Form("log10(L%d_E/Total_E)>>h1_e[%d]",j,j),HET,""); h1_e[j]->Scale(1.0/h1_e[j]->Integral());h1_e[j]->SetLineColor(kOrange-3);h1_e[j]->SetMarkerColor(kOrange-3);h1_e[j]->SetLineWidth(2);
                helium4_tree->Draw(Form("log10(L%d_E/Total_E)>>h1_h[%d]",j,j),HET,"");  h1_h[j]->Scale(1.0/h1_h[j]->Integral());h1_h[j]->SetLineColor(kGreen-3); h1_h[j]->SetMarkerColor(kGreen-3); h1_h[j]->SetLineWidth(2);
                
                h1_p[j]->Draw();
                h1_d[j]->Draw("same");
                h1_e[j]->Draw("same");
                h1_h[j]->Draw("same");
                
                
                double quantiles[3] = {0.16, 0.50, 0.84};  // Percentiles
                double p_values[3];  // Will store the x-values corresponding to the percentiles
                double d_values[3];  // Will store the x-values corresponding to the percentiles
                double e_values[3];  // Will store the x-values corresponding to the percentiles
                double h_values[3];  // Will store the x-values corresponding to the percentiles

                h1_p[j]->GetQuantiles(3, p_values, quantiles);
                h1_d[j]->GetQuantiles(3, d_values, quantiles);
                h1_e[j]->GetQuantiles(3, e_values, quantiles);
                h1_h[j]->GetQuantiles(3, h_values, quantiles);
                // cout << p_values[0] << " , " << p_values[1] << " , " << p_values[2]<< endl;

                Proton_Ratio[j] = p_values[1];     Proton_Ratio_LL[j]  = p_values[1] - p_values[0];   Proton_Ratio_UL[j]= p_values[2] - p_values[1];
                Deuteron_Ratio[j] = d_values[1];   Deuteron_Ratio_LL[j]= d_values[1] - d_values[0];   Deuteron_Ratio_UL[j]= d_values[2] - d_values[1];
                Electron_Ratio[j] = e_values[1];   Electron_Ratio_LL[j]= e_values[1] - e_values[0];   Electron_Ratio_UL[j]= e_values[2] - e_values[1];
                Helium4_Ratio[j] = h_values[1];    Helium4_Ratio_LL[j] = h_values[1] - h_values[0];   Helium4_Ratio_UL[j]= h_values[2] - h_values[1];

                Layer[j] = 0.5 + j;
                Layer_Err[j] = 0.5;

                cout << Proton_Ratio[j]  << " , " << Proton_Ratio_LL[j]<< " , " << Proton_Ratio_UL[j] << endl; 
                cout << Layer[j]  << " , " << Layer_Err[j] << " , " << Layer_Err[j] << endl; 

            }

            else // (j==14)    
            {
                TLatex *tex = new TLatex(0.1,0.9,Form("IncidentParicle %dGeV",int(Energy[i])));tex->SetNDC();tex->Draw(); 
                auto legend1 = new TLegend(0.12, 0.12, 0.88, 0.88);
                legend1->AddEntry(h1_p[0], "Proton", "l");
                legend1->AddEntry(h1_d[0], "Deuteron", "l");
                legend1->AddEntry(h1_e[0], "Electron", "l");
                legend1->AddEntry(h1_h[0], "Helium4", "l");         
                legend1->Draw();       
            }

        }
        c1->SaveAs( Form("/Users/xiongzheng/software/B4/B4c/Script/EnergyDep/Edep_Ratio_perLayer_%dGeV.pdf",int(Energy[i])));
        
        auto c2 = new TCanvas("c2","c2",1000,1000);
        // c2->cd();
        auto gre_p = new TGraphAsymmErrors(14,Layer,Proton_Ratio  ,Layer_Err,Layer_Err,Proton_Ratio_LL  ,Proton_Ratio_UL);
        auto gre_d = new TGraphAsymmErrors(14,Layer,Deuteron_Ratio,Layer_Err,Layer_Err,Deuteron_Ratio_LL,Deuteron_Ratio_UL);
        auto gre_e = new TGraphAsymmErrors(14,Layer,Electron_Ratio,Layer_Err,Layer_Err,Electron_Ratio_LL,Electron_Ratio_UL);
        auto gre_h = new TGraphAsymmErrors(14,Layer,Helium4_Ratio ,Layer_Err,Layer_Err,Helium4_Ratio_LL ,Helium4_Ratio_UL);
        gre_p->SetTitle(Form("Incident Energy %d GeV ; BGO Layer; log10(Deposit Energy Ratio)",int(Energy[i])));
        gre_p->SetMarkerStyle(22);
        
        gre_e->SetMarkerColor(kOrange-3);
        gre_e->SetLineColor(kOrange-3);
        gre_p->SetMarkerStyle(20);
        gre_p->SetMarkerColor(kRed);
        gre_p->SetLineColor(kRed);
        gre_d->SetMarkerStyle(21);
        gre_d->SetMarkerColor(kBlue);
        gre_d->SetLineColor(kBlue);
        gre_h->SetMarkerStyle(23);
        gre_h->SetMarkerColor(kGreen-3);
        gre_h->SetLineColor(kGreen-3);

        gre_p->SetLineWidth(2);
        gre_d->SetLineWidth(2);
        gre_e->SetLineWidth(2);
        gre_h->SetLineWidth(2);
    
        gre_p->Draw("AP");
        gre_d->Draw("PSAME");
        gre_e->Draw("PSAME");
        gre_h->Draw("PSAME");
        auto legend2 = new TLegend(0.42, 0.12, 0.58, 0.32);
        legend2->SetNColumns(2);
        legend2->AddEntry(gre_p, "HET Proton", "ep");
        legend2->AddEntry(gre_d, "HET Deuteron", "ep");
        legend2->AddEntry(gre_e, "HET Electron", "ep");
        legend2->AddEntry(gre_h, "HET Helium4", "ep");
        legend2->Draw();

        c2->SaveAs( Form("/Users/xiongzheng/software/B4/B4c/Script/EnergyDep/Edep_Ratio_BGOLayer_%dGeV.pdf",int(Energy[i])));

    }
}