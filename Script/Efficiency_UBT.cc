void Efficiency_UBT()
{
    double Proton_Eff[18]={0};
    double Proton_Eff_UBT[18]={0};

    double Deuteron_Eff[18]={0};
    double Deuteron_Eff_UBT[18]={0};

    double Electron_Eff[18]={0};
    double Electron_Eff_UBT[18]={0};

    double Helium4_Eff[18]={0};
    double Helium4_Eff_UBT[18]={0};

    double Energy[18]={0};
    double Energy_Err[18]={0};
    double Uncertainty[18]={0};
    double n_BGO = TMath::Na()*7.13/1245.8344; // cm-3
    TH1D *h1_p[18]; TH1D *h2_p[18]; TH1D *h3_p[18];
    TH1D *h1_d[18]; TH1D *h2_d[18]; TH1D *h3_d[18];
    TH1D *h1_e[18]; TH1D *h2_e[18]; TH1D *h3_e[18];
    TH1D *h1_h[18]; TH1D *h2_h[18]; TH1D *h3_h[18];

    TCut UBT = "L0_E+L1_E>0.0092";
    TCut HET = "(L0_E+L1_E+L2_E>0.23) && (L3_E>0.046)";

    for (int i = 0; i < 18; i++)
    {
        if(i<10)  {Energy[i] =  (i+1)*10; Energy_Err[i] = 5;}
        else   {Energy[i] =  i*100-800;Energy_Err[i] = 50;}

        auto proton_file = TFile::Open(Form("/Users/xiongzheng/software/B4/B4c/Root/Proton_%dGeV.root",int(Energy[i])));
        auto proton_tree = (TTree*)proton_file->Get("B4");
        h1_p[i] = new TH1D(Form("h1_p[%d]",i),Form("h1_p[%d]",i),100,0,1);
        h2_p[i] = new TH1D(Form("h2_p[%d]",i),Form("h2_p[%d]",i),100,0,1);
        h3_p[i] = new TH1D(Form("h3_p[%d]",i),Form("h3_p[%d]",i),100,0,1);
        proton_tree->Draw(Form("Total_E/Energy>>h1_p[%d]",i),"","");
        proton_tree->Draw(Form("Total_E/Energy>>h2_p[%d]",i),HET,"");
        proton_tree->Draw(Form("Total_E/Energy>>h3_p[%d]",i),UBT,"");
        Proton_Eff[i]     = h2_p[i]->GetSum()/h1_p[i]->GetSum();
        Proton_Eff_UBT[i] = h3_p[i]->GetSum()/h1_p[i]->GetSum();

        auto deuteron_file = TFile::Open(Form("/Users/xiongzheng/software/B4/B4c/Root/Deuteron_%dGeV.root",int(Energy[i])));
        auto deuteron_tree = (TTree*)deuteron_file->Get("B4");
        h1_d[i] = new TH1D(Form("h1_d[%d]",i),Form("h1_d[%d]",i),100,0,1);
        h2_d[i] = new TH1D(Form("h2_d[%d]",i),Form("h2_d[%d]",i),100,0,1);
        h3_d[i] = new TH1D(Form("h3_d[%d]",i),Form("h3_d[%d]",i),100,0,1);
        deuteron_tree->Draw(Form("Total_E/Energy>>h1_d[%d]",i),"", "");
        deuteron_tree->Draw(Form("Total_E/Energy>>h2_d[%d]",i),HET,"");
        deuteron_tree->Draw(Form("Total_E/Energy>>h3_d[%d]",i),UBT,"");
        Deuteron_Eff[i]     = h2_d[i]->GetSum()/h1_d[i]->GetSum();
        Deuteron_Eff_UBT[i] = h3_d[i]->GetSum()/h1_d[i]->GetSum();

        auto electron_file = TFile::Open(Form("/Users/xiongzheng/software/B4/B4c/Root/Electron_%dGeV.root",int(Energy[i])));
        auto electron_tree = (TTree*)electron_file->Get("B4");
        h1_e[i] = new TH1D(Form("h1_e[%d]",i),Form("h1_e[%d]",i),100,0,1);
        h2_e[i] = new TH1D(Form("h2_e[%d]",i),Form("h2_e[%d]",i),100,0,1);
        h3_e[i] = new TH1D(Form("h3_e[%d]",i),Form("h3_e[%d]",i),100,0,1);
        electron_tree->Draw(Form("Total_E/Energy>>h1_e[%d]",i),"","");
        electron_tree->Draw(Form("Total_E/Energy>>h2_e[%d]",i), HET,"");
        electron_tree->Draw(Form("Total_E/Energy>>h3_e[%d]",i), UBT,"");
        Electron_Eff[i]     = h2_e[i]->GetSum()/h1_e[i]->GetSum();
        Electron_Eff_UBT[i] = h3_e[i]->GetSum()/h1_e[i]->GetSum();

        auto helium4_file = TFile::Open(Form("/Users/xiongzheng/software/B4/B4c/Root/Helium4_%dGeV.root",int(Energy[i])));
        auto helium4_tree = (TTree*)helium4_file->Get("B4");
        h1_h[i] = new TH1D(Form("h1_h[%d]",i),Form("h1_h[%d]",i),100,0,1);
        h2_h[i] = new TH1D(Form("h2_h[%d]",i),Form("h2_h[%d]",i),100,0,1);
        h3_h[i] = new TH1D(Form("h3_h[%d]",i),Form("h3_h[%d]",i),100,0,1);
        helium4_tree->Draw(Form("Total_E/Energy>>h1_h[%d]",i), "", "");
        helium4_tree->Draw(Form("Total_E/Energy>>h2_h[%d]",i),  HET,"");
        helium4_tree->Draw(Form("Total_E/Energy>>h3_h[%d]",i),  UBT,"");
        Helium4_Eff[i]     = h2_h[i]->GetSum()/h1_h[i]->GetSum();
        Helium4_Eff_UBT[i] = h3_h[i]->GetSum()/h1_h[i]->GetSum();

        cout << "Energy = " << int(Energy[i]) << " GeV !" << " He4 eff : " << h2_h[i]->GetSum() <<endl;

    }
    

    auto gre_p     = new TGraphErrors(18, Energy, Proton_Eff, Energy_Err, Uncertainty);
    auto gre_p_UBT = new TGraphErrors(18, Energy, Proton_Eff_UBT, Energy_Err, Uncertainty);
    
    gre_p->SetTitle("High-Energy Trigger; Kinetic Energy (GeV); Trigger Efficiency");
    gre_p->SetMarkerStyle(20);
    gre_p->SetMarkerColor(kRed);
    gre_p->SetLineColor(kRed);
    gre_p_UBT->SetTitle("Unbiased Trigger;Kinetic Energy (GeV); Trigger Efficiency");
    gre_p_UBT->SetMarkerStyle(24);
    gre_p_UBT->SetMarkerColor(kRed);
    gre_p_UBT->SetLineColor(kRed);

    auto gre_d     = new TGraphErrors(18, Energy, Deuteron_Eff, Energy_Err, Uncertainty);
    auto gre_d_UBT = new TGraphErrors(18, Energy, Deuteron_Eff_UBT, Energy_Err, Uncertainty);

    gre_d->SetMarkerStyle(21);
    gre_d->SetMarkerColor(kBlue);
    gre_d->SetLineColor(kBlue);
    gre_d_UBT->SetMarkerStyle(25);
    gre_d_UBT->SetMarkerColor(kBlue);
    gre_d_UBT->SetLineColor(kBlue);

    auto gre_e     = new TGraphErrors(18, Energy, Electron_Eff, Energy_Err, Uncertainty);
    auto gre_e_UBT = new TGraphErrors(18, Energy, Electron_Eff_UBT, Energy_Err, Uncertainty);

    gre_e->SetMarkerStyle(22);
    gre_e->SetMarkerColor(kOrange-3);
    gre_e->SetLineColor(kOrange-3);
    gre_e_UBT->SetMarkerStyle(26);
    gre_e_UBT->SetMarkerColor(kOrange-3);
    gre_e_UBT->SetLineColor(kOrange-3);


    auto gre_h     = new TGraphErrors(18, Energy, Helium4_Eff, Energy_Err, Uncertainty);
    auto gre_h_UBT = new TGraphErrors(18, Energy, Helium4_Eff_UBT, Energy_Err, Uncertainty);

    gre_h->SetMarkerStyle(23);
    gre_h->SetMarkerColor(kGreen-3);
    gre_h->SetLineColor(kGreen-3);
    gre_h_UBT->SetMarkerStyle(32);
    gre_h_UBT->SetMarkerColor(kGreen-3);
    gre_h_UBT->SetLineColor(kGreen-3);

    auto c0 = new TCanvas("c0","c0",1200,1200);
    c0->Clear();
    c0->cd();
    gPad->SetLogx();
    gre_p_UBT->Draw("AP");
    gre_p_UBT->GetYaxis()->SetRangeUser(0.999, 1.001);
    gre_p_UBT->GetYaxis()->SetNdivisions(505);
    // gre_p_UBT->GetYaxis()->SetLabelSize(0.04);
    // gre_p_UBT->GetYaxis()->SetTitleSize(0.07);
    gre_p_UBT->GetYaxis()->SetTitleOffset(1.45);

    gre_d_UBT->Draw("PSAME");
    gre_e_UBT->Draw("PSAME");
    gre_h_UBT->Draw("PSAME");

    auto legend1 = new TLegend(0.60, 0.68, 0.88, 0.88);
    legend1->SetNColumns(2);
    legend1->AddEntry(gre_p_UBT, "UBT Proton", "ep");
    legend1->AddEntry(gre_d_UBT, "UBT Deuteron", "ep");
    legend1->AddEntry(gre_e_UBT, "UBT Electron", "ep");
    legend1->AddEntry(gre_h_UBT, "UBT Helium4", "ep");
    legend1->Draw();

    auto c1 = new TCanvas("c1","c1",1200,1200);
    c1->Clear();
    c1->cd();
    gPad->SetLogx();


    gre_p->Draw("AP");
    gre_d->Draw("PSAME");
    gre_e->Draw("PSAME");
    gre_h->Draw("PSAME");
    gre_p->GetYaxis()->SetRangeUser(0.3, 1.05);
    gre_p->GetYaxis()->SetNdivisions(505);
    // gre_p->GetYaxis()->SetLabelSize(0.05);
    // gre_p->GetYaxis()->SetTitleSize(0.07);
    // gre_p->GetYaxis()->SetTitleOffset(0.5);
    // gre_p->GetXaxis()->SetLabelSize(0.06);
    // gre_p->GetXaxis()->SetTitleSize(0.07);

    auto legend2 = new TLegend(0.60, 0.12, 0.88, 0.32);
    legend2->SetNColumns(2);
    legend2->AddEntry(gre_p, "HET Proton", "ep");
    legend2->AddEntry(gre_d, "HET Deuteron", "ep");
    legend2->AddEntry(gre_e, "HET Electron", "ep");
    legend2->AddEntry(gre_h, "HET Helium4", "ep");
    legend2->Draw();

}