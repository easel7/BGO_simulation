void EnergyLong_E_SingleLayer()
{
    auto proton_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Weight/Proton_PowerLaw.root");
    auto proton_tree = (TTree*)proton_file->Get("B4");
    auto deuteron_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Weight/Deuteron_PowerLaw.root");
    auto deuteron_tree = (TTree*)deuteron_file->Get("B4");
    auto electron_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Weight/Electron_PowerLaw.root");
    auto electron_tree = (TTree*)electron_file->Get("B4");
    auto helium4_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Weight/Helium4_PowerLaw.root");
    auto helium4_tree = (TTree*)helium4_file->Get("B4");
    auto helium3_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Weight/Helium3_PowerLaw.root");
    auto helium3_tree = (TTree*)helium3_file->Get("B4");
    auto carbon_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Weight/Carbon_PowerLaw.root");
    auto carbon_tree = (TTree*)carbon_file->Get("B4");
    
    double Proton_Ratio[14]={0};     double Deuteron_Ratio[14]={0};    double Electron_Ratio[14]={0};    double Helium4_Ratio[14]={0};     double Helium3_Ratio[14]={0};     double Carbon_Ratio[14]={0};        
    double Proton_Ratio_LL[14]={0};  double Deuteron_Ratio_LL[14]={0}; double Electron_Ratio_LL[14]={0}; double Helium4_Ratio_LL[14]={0};  double Helium3_Ratio_LL[14]={0};  double Carbon_Ratio_LL[14]={0};        
    double Proton_Ratio_UL[14]={0};  double Deuteron_Ratio_UL[14]={0}; double Electron_Ratio_UL[14]={0}; double Helium4_Ratio_UL[14]={0};  double Helium3_Ratio_UL[14]={0};  double Carbon_Ratio_UL[14]={0};     

    double Layer[14]={0};
    double Layer_Err[14]={0};
    double Energy[13]={0};
    double Energy_Err[13]={0};
    double Energy_LL[13]={0};      
    double Energy_UL[13]={0};
    // Depsit and Layer
    TH1D *h1_p[13][14];     TH1D *h2_p[13][14];
    TH1D *h1_d[13][14];     TH1D *h2_d[13][14];
    TH1D *h1_e[13][14];     TH1D *h2_e[13][14];
    TH1D *h1_h[13][14];     TH1D *h2_h[13][14];
    TH1D *h1_H[13][14];     TH1D *h2_H[13][14];
    TH1D *h1_c[13][14];     TH1D *h2_c[13][14];

    for (int i = 0; i < 1; i++) // Deposit Energy Bin
    {
        Energy[i]    =  0.2*i+1.1;
        Energy_Err[i] =  0.1; 
        Energy_LL[i] =  0.2*i+1.0;
        Energy_UL[i] =  0.2*i+1.2;
        // TCut HET = Form(" (log10(Total_E)>%.2f && log10(Total_E)<=%.2f)",Energy_LL[i],Energy_UL[i]);
        // TCut HET = Form(" (First_Had_Layer == -1 || First_Had_Layer>0) && (log10(Total_E)>%.2f && log10(Total_E)<=%.2f)",Energy_LL[i],Energy_UL[i]); // no hadronic interaction at Layer0
        TCut HET = Form(" (First_Had_Layer==0 && First_Had_Type==1 ) && (log10(Total_E)>%.2f && log10(Total_E)<=%.2f)",Energy_LL[i],Energy_UL[i]);    // hadronic interaction at Layer0

        cout << "Deposit Energy Range = [ " << Energy_LL[i] << " , " << Energy_UL[i] << " ]"<< endl;
        auto c1 = new TCanvas("c1","c1",1200,600);
        c1->Clear();
        c1->Divide(2,1);
        gStyle->SetOptStat(0);
    
        c1->cd(1);
        
        h1_p[i][0] = new TH1D(Form("h1_p[%d][%d]",i,0), Form("h1_p[%d][%d]",i,0),60,-2.5,3.5);  
        h1_d[i][0] = new TH1D(Form("h1_d[%d][%d]",i,0), Form("h1_d[%d][%d]",i,0),60,-2.5,3.5);  
        h1_e[i][0] = new TH1D(Form("h1_e[%d][%d]",i,0), Form("h1_e[%d][%d]",i,0),60,-2.5,3.5);  
        h1_h[i][0] = new TH1D(Form("h1_h[%d][%d]",i,0), Form("h1_h[%d][%d]",i,0),60,-2.5,3.5);  
        h1_H[i][0] = new TH1D(Form("h1_H[%d][%d]",i,0), Form("h1_H[%d][%d]",i,0),60,-2.5,3.5);  
        h1_c[i][0] = new TH1D(Form("h1_c[%d][%d]",i,0), Form("h1_c[%d][%d]",i,0),60,-2.5,3.5);  

        h2_p[i][0] = new TH1D(Form("h2_p[%d][%d]",i,0), Form("h2_p[%d][%d]",i,0),75,0,150);  
        h2_d[i][0] = new TH1D(Form("h2_d[%d][%d]",i,0), Form("h2_d[%d][%d]",i,0),75,0,150);  
        h2_e[i][0] = new TH1D(Form("h2_e[%d][%d]",i,0), Form("h2_e[%d][%d]",i,0),75,0,150);  
        h2_h[i][0] = new TH1D(Form("h2_h[%d][%d]",i,0), Form("h2_h[%d][%d]",i,0),75,0,150);  
        h2_H[i][0] = new TH1D(Form("h2_H[%d][%d]",i,0), Form("h2_H[%d][%d]",i,0),75,0,150);  
        h2_c[i][0] = new TH1D(Form("h2_c[%d][%d]",i,0), Form("h2_c[%d][%d]",i,0),75,0,150);  


        proton_tree  ->Draw(Form("log10(L%d_E)>>h1_p[%d][%d]",0,i,0),HET,""); h1_p[i][0]->Sumw2(); h1_p[i][0]->Scale(1.0/h1_p[i][0]->Integral());h1_p[i][0]->SetLineColor(kRed);     h1_p[i][0]->SetMarkerColor(kRed);     h1_p[i][0]->SetLineWidth(2); 
        deuteron_tree->Draw(Form("log10(L%d_E)>>h1_d[%d][%d]",0,i,0),HET,""); h1_d[i][0]->Sumw2(); h1_d[i][0]->Scale(1.0/h1_d[i][0]->Integral());h1_d[i][0]->SetLineColor(kBlue);    h1_d[i][0]->SetMarkerColor(kBlue);    h1_d[i][0]->SetLineWidth(2);
        electron_tree->Draw(Form("log10(L%d_E)>>h1_e[%d][%d]",0,i,0),HET,""); h1_e[i][0]->Sumw2(); h1_e[i][0]->Scale(1.0/h1_e[i][0]->Integral());h1_e[i][0]->SetLineColor(kOrange-3);h1_e[i][0]->SetMarkerColor(kOrange-3);h1_e[i][0]->SetLineWidth(2);
        helium4_tree ->Draw(Form("log10(L%d_E)>>h1_h[%d][%d]",0,i,0),HET,""); h1_h[i][0]->Sumw2(); h1_h[i][0]->Scale(1.0/h1_h[i][0]->Integral());h1_h[i][0]->SetLineColor(kGreen-3); h1_h[i][0]->SetMarkerColor(kGreen-3); h1_h[i][0]->SetLineWidth(2);
        helium3_tree ->Draw(Form("log10(L%d_E)>>h1_H[%d][%d]",0,i,0),HET,""); h1_H[i][0]->Sumw2(); h1_H[i][0]->Scale(1.0/h1_H[i][0]->Integral());h1_H[i][0]->SetLineColor(kGreen-3); h1_H[i][0]->SetMarkerColor(kGreen-3); h1_H[i][0]->SetLineWidth(2);
        carbon_tree  ->Draw(Form("log10(L%d_E)>>h1_c[%d][%d]",0,i,0),HET,""); h1_c[i][0]->Sumw2(); h1_c[i][0]->Scale(1.0/h1_c[i][0]->Integral());h1_c[i][0]->SetLineColor(kMagenta); h1_c[i][0]->SetMarkerColor(kMagenta); h1_c[i][0]->SetLineWidth(2);

        proton_tree  ->Draw(Form("First_Had_Second>>h2_p[%d][%d]",i,0),HET,""); h2_p[i][0]->Sumw2(); h2_p[i][0]->Scale(1.0/h2_p[i][0]->Integral());h2_p[i][0]->SetLineColor(kRed);     h2_p[i][0]->SetMarkerColor(kRed);     h2_p[i][0]->SetLineWidth(2); 
        deuteron_tree->Draw(Form("First_Had_Second>>h2_d[%d][%d]",i,0),HET,""); h2_d[i][0]->Sumw2(); h2_d[i][0]->Scale(1.0/h2_d[i][0]->Integral());h2_d[i][0]->SetLineColor(kBlue);    h2_d[i][0]->SetMarkerColor(kBlue);    h2_d[i][0]->SetLineWidth(2);
        electron_tree->Draw(Form("First_Had_Second>>h2_e[%d][%d]",i,0),HET,""); h2_e[i][0]->Sumw2(); h2_e[i][0]->Scale(1.0/h2_e[i][0]->Integral());h2_e[i][0]->SetLineColor(kOrange-3);h2_e[i][0]->SetMarkerColor(kOrange-3);h2_e[i][0]->SetLineWidth(2);
        helium4_tree ->Draw(Form("First_Had_Second>>h2_h[%d][%d]",i,0),HET,""); h2_h[i][0]->Sumw2(); h2_h[i][0]->Scale(1.0/h2_h[i][0]->Integral());h2_h[i][0]->SetLineColor(kGreen-3); h2_h[i][0]->SetMarkerColor(kGreen-3); h2_h[i][0]->SetLineWidth(2);
        helium3_tree ->Draw(Form("First_Had_Second>>h2_H[%d][%d]",i,0),HET,""); h2_H[i][0]->Sumw2(); h2_H[i][0]->Scale(1.0/h2_H[i][0]->Integral());h2_H[i][0]->SetLineColor(kGreen-3); h2_H[i][0]->SetMarkerColor(kGreen-3); h2_H[i][0]->SetLineWidth(2);
        carbon_tree  ->Draw(Form("First_Had_Second>>h2_c[%d][%d]",i,0),HET,""); h2_c[i][0]->Sumw2(); h2_c[i][0]->Scale(1.0/h2_c[i][0]->Integral());h2_c[i][0]->SetLineColor(kMagenta); h2_c[i][0]->SetMarkerColor(kMagenta); h2_c[i][0]->SetLineWidth(2);

            
        h1_h[i][0]->GetYaxis()->SetRangeUser(0,h1_c[i][0]->GetMaximum()*1.5);h1_h[i][0]->SetTitle(Form("EdepRatio Distrubution in L%d;log_{10}(Energy Deposit/GeV);Normalized Count",0));
        
        auto line0_MIP = new TLine(log10(0.03),0,log10(0.03),h1_h[i][0]->GetMaximum());
        auto line1_MIP = new TLine(log10(0.03*4),0,log10(0.03*4),h1_h[i][0]->GetMaximum());
        auto line2_MIP = new TLine(log10(0.03*36),0,log10(0.03*36),h1_h[i][0]->GetMaximum());
        line1_MIP->SetLineStyle(2);
        line2_MIP->SetLineStyle(7);

        auto line0_PEAK = new TLine(log10(0.03*20),0,log10(0.03*20),h1_h[i][0]->GetMaximum());
        auto line1_PEAK = new TLine(log10(0.03*20),0,log10(0.03*20),h1_h[i][0]->GetMaximum());
        line0_PEAK->SetLineColor(kRed);
        line1_PEAK->SetLineColor(kRed);
        line0_PEAK->SetLineStyle(3);
        line1_PEAK->SetLineStyle(4);

        h1_p[i][0]->Integral(0,15);
        h1_d[i][0]->Integral(0,15);

        cout << "Integral peak (-2.5,-0.7)= " <<  h1_p[i][0]->Integral(1,18) << " ,  Ratio of 1 Secondary : " << h2_p[i][0]->Integral(1,1) <<  endl;
        cout << "Integral peak (-2.5,-0.7)= " <<  h1_d[i][0]->Integral(1,18) << " ,  Ratio of 1 Secondary : " << h2_d[i][0]->Integral(1,1) <<  endl;
        cout << "Integral peak (-2.5,-0.5)= " <<  h1_h[i][0]->Integral(1,20) << " ,  Ratio of 1 Secondary : " << h2_h[i][0]->Integral(1,1) <<  endl;

        // h1_e[i][0]->Draw("");
        h1_h[i][0]->Draw("");
        h1_H[i][0]->Draw("SAME");
        h1_d[i][0]->Draw("SAME");
        h1_p[i][0]->Draw("SAME");
        h1_c[i][0]->Draw("SAME");
        line0_MIP->Draw();
        line1_MIP->Draw();
        line2_MIP->Draw();
        line0_PEAK->Draw();
        // line1_PEAK->Draw();

        double quantiles[3] = {0.16, 0.50, 0.84};  // Percentiles
        double p_values[3];  h1_p[i][0]->GetQuantiles(3, p_values, quantiles);
        double d_values[3];  h1_d[i][0]->GetQuantiles(3, d_values, quantiles);
        double e_values[3];  h1_e[i][0]->GetQuantiles(3, e_values, quantiles);
        double h_values[3];  h1_h[i][0]->GetQuantiles(3, h_values, quantiles);
        double H_values[3];  h1_H[i][0]->GetQuantiles(3, H_values, quantiles);
        double c_values[3];  h1_c[i][0]->GetQuantiles(3, c_values, quantiles);

        Proton_Ratio[i]   = p_values[1];    Proton_Ratio_LL[i]  = p_values[1] - p_values[0];   Proton_Ratio_UL[i]= p_values[2] - p_values[1];
        Deuteron_Ratio[i] = d_values[1];    Deuteron_Ratio_LL[i]= d_values[1] - d_values[0];   Deuteron_Ratio_UL[i]= d_values[2] - d_values[1];
        Electron_Ratio[i] = e_values[1];    Electron_Ratio_LL[i]= e_values[1] - e_values[0];   Electron_Ratio_UL[i]= e_values[2] - e_values[1];
        Helium4_Ratio[i]  = h_values[1];    Helium4_Ratio_LL[i] = h_values[1] - h_values[0];   Helium4_Ratio_UL[i]= h_values[2] - h_values[1];
        Helium3_Ratio[i]  = H_values[1];    Helium3_Ratio_LL[i] = H_values[1] - H_values[0];   Helium3_Ratio_UL[i]= H_values[2] - H_values[1];
        Carbon_Ratio[i]   = c_values[1];    Carbon_Ratio_LL[i]  = c_values[1] - c_values[0];   Carbon_Ratio_UL[i]= c_values[2] - c_values[1];

        c1->cd(2);
        h2_h[i][0]->GetYaxis()->SetRangeUser(0,h2_h[i][0]->GetMaximum()*1.5);h2_h[i][0]->SetTitle(Form("No. Secondaries Distrubution in L%d;No. Secondaries;Normalized Count",0));
        h2_h[i][0]->Draw("");
        h2_H[i][0]->Draw("same");
        h2_c[i][0]->Draw("same");
        h2_d[i][0]->Draw("same");
        h2_p[i][0]->Draw("same");

        // TLatex *tex = new TLatex(0.1,0.9,Form("Deposit Energy[%.2fGeV, %.2fGeV]",pow(10,Energy_LL[i]),pow(10,Energy_UL[i])));tex->SetNDC();tex->Draw(); 
        // auto legend1 = new TLegend(0.12, 0.12, 0.88, 0.88);
        // legend1->AddEntry(h1_p[i][0], "Proton", "l");
        // legend1->AddEntry(h1_d[i][0], "Deuteron", "l");
        // // legend1->AddEntry(h1_e[i][0], "Electron", "l");
        // legend1->AddEntry(h1_h[i][0], "Helium4", "l");         
        // legend1->AddEntry(h1_H[i][0], "Helium3", "l");         
        // legend1->AddEntry(h1_c[i][0], "Carbon", "l");         
        // legend1->Draw();       
            
        c1->Update();
        c1->SaveAs(Form("/Users/xiongzheng/software/B4/B4c/Script/EnergyLong/EnergyLong_L0_%.2f_%.2f.pdf",Energy_LL[i],Energy_UL[i]));
    }
    

        auto c2 = new TCanvas("c2","c2",1000,1000);
        // c2->cd();
        auto gre_p = new TGraphAsymmErrors(13,Energy,Proton_Ratio  ,Energy_Err,Energy_Err,Proton_Ratio_LL  ,Proton_Ratio_UL);
        auto gre_d = new TGraphAsymmErrors(13,Energy,Deuteron_Ratio,Energy_Err,Energy_Err,Deuteron_Ratio_LL,Deuteron_Ratio_UL);
        auto gre_e = new TGraphAsymmErrors(13,Energy,Electron_Ratio,Energy_Err,Energy_Err,Electron_Ratio_LL,Electron_Ratio_UL);
        auto gre_h = new TGraphAsymmErrors(13,Energy,Helium4_Ratio ,Energy_Err,Energy_Err,Helium4_Ratio_LL ,Helium4_Ratio_UL);
        auto gre_H = new TGraphAsymmErrors(13,Energy,Helium3_Ratio ,Energy_Err,Energy_Err,Helium3_Ratio_LL ,Helium3_Ratio_UL);
        auto gre_c = new TGraphAsymmErrors(13,Energy,Carbon_Ratio  ,Energy_Err,Energy_Err,Carbon_Ratio_LL ,Carbon_Ratio_UL);

        gre_h->SetTitle(" ; log_{10}(Deposit Energy/GeV); log10(Deposit Energy in L0/GeV)");
        gre_h->SetMarkerStyle(22);
        gre_h->GetYaxis()->SetRangeUser(-2.5,3);
        
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
        gre_H->SetMarkerStyle(32);
        gre_H->SetMarkerColor(kGreen-3);
        gre_H->SetLineColor(kGreen-3);
        gre_c->SetMarkerStyle(23);
        gre_c->SetMarkerColor(kMagenta);
        gre_c->SetLineColor(kMagenta);

        gre_p->SetLineWidth(2);
        gre_d->SetLineWidth(2);
        gre_e->SetLineWidth(2);
        gre_h->SetLineWidth(2);
        gre_H->SetLineWidth(2);
        gre_c->SetLineWidth(2);

        // gre_e->Draw("AP");
        gre_h->Draw("AP");
        gre_H->Draw("PSAME");
        gre_c->Draw("PSAME");
        gre_d->Draw("PSAME");
        gre_p->Draw("PSAME");

        auto legend2 = new TLegend(0.72, 0.12, 0.88, 0.32);
        legend2->SetNColumns(2);
        legend2->AddEntry(gre_p, "HET Proton", "ep");
        legend2->AddEntry(gre_d, "HET Deuteron", "ep");
        // legend2->AddEntry(gre_e, "HET Electron", "ep");
        legend2->AddEntry(gre_h, "HET Helium4", "ep");
        legend2->AddEntry(gre_H, "HET Helium3", "ep");
        legend2->AddEntry(gre_c, "HET Carbon", "ep");
        legend2->Draw();

    
        c2->SaveAs("/Users/xiongzheng/software/B4/B4c/Script/EnergyLong/LayerDistribution_L0.pdf");
    
}
