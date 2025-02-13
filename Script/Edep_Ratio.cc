void Edep_Ratio()
{
    double Proton_Edep[19]={0};
    double Proton_Edep_Err[19]={0};

    double Deuteron_Edep[19]={0};
    double Deuteron_Edep_Err[19]={0};

    double Electron_Edep[19]={0};
    double Electron_Edep_Err[19]={0};

    double Helium4_Edep[19]={0};
    double Helium4_Edep_Err[19]={0};

    double Energy[19]={0};
    double Energy_Err[19]={0};
    TH1D *h1_e[19];  TF1  *fitFunc_e[19];
    TH1D *h1_p[19];  TF1  *fitFunc_p[19];
    TH1D *h1_d[19];  TF1  *fitFunc_d[19];
    TH1D *h1_h[19];  TF1  *fitFunc_h[19];

    TCut UBT = "L0_E+L1_E>0.0092";
    TCut HET = "(L0_E+L1_E+L2_E>0.23) && (L3_E>0.046)";

    for (int i = 0; i < 19; i++)
    {
        if(i<9)  {Energy[i] =  (i+1)*10;}
        else   {Energy[i] =  i*100-800;}
        cout << "Energy = " << int(Energy[i]) << " GeV !" << endl;

        auto proton_file = TFile::Open(Form("/Users/xiongzheng/software/B4/B4c/Root/Proton_%dGeV.root",int(Energy[i])));
        auto proton_tree = (TTree*)proton_file->Get("B4");
        auto deuteron_file = TFile::Open(Form("/Users/xiongzheng/software/B4/B4c/Root/Deuteron_%dGeV.root",int(Energy[i])));
        auto deuteron_tree = (TTree*)deuteron_file->Get("B4");
        auto electron_file = TFile::Open(Form("/Users/xiongzheng/software/B4/B4c/Root/Electron_%dGeV.root",int(Energy[i])));
        auto electron_tree = (TTree*)electron_file->Get("B4");
        auto helium4_file = TFile::Open(Form("/Users/xiongzheng/software/B4/B4c/Root/Helium4_%dGeV.root",int(Energy[i])));
        auto helium4_tree = (TTree*)helium4_file->Get("B4");

        h1_p[i] = new TH1D(Form("h1_p[%d]",i),Form("h1_p[%d]",i),100,0,1); 
        h1_d[i] = new TH1D(Form("h1_d[%d]",i),Form("h1_d[%d]",i),100,0,1); 
        h1_e[i] = new TH1D(Form("h1_e[%d]",i),Form("h1_e[%d]",i),100,0,1); 
        h1_h[i] = new TH1D(Form("h1_h[%d]",i),Form("h1_h[%d]",i),100,0,1); 

        proton_tree->Draw(Form("Total_E/Energy>>h1_p[%d]",i), HET, "");   h1_p[i]->SetLineColor(kRed);      h1_p[i]->SetMarkerColor(kRed);     h1_p[i]->SetLineWidth(2);
        deuteron_tree->Draw(Form("Total_E/Energy>>h1_d[%d]",i), HET, ""); h1_d[i]->SetLineColor(kBlue);     h1_d[i]->SetMarkerColor(kBlue);    h1_d[i]->SetLineWidth(2);
        electron_tree->Draw(Form("Total_E/Energy>>h1_e[%d]",i), HET, ""); h1_e[i]->SetLineColor(kOrange-3); h1_e[i]->SetMarkerColor(kOrange-3);h1_e[i]->SetLineWidth(2);
        helium4_tree->Draw(Form("Total_E/Energy>>h1_h[%d]",i), HET, "");  h1_h[i]->SetLineColor(kGreen-3);  h1_h[i]->SetMarkerColor(kGreen-3); h1_h[i]->SetLineWidth(2);
        
        h1_e[i]->SetTitle(Form("%d GeV - Deposit Energy/Incident Energy;Energy Deposit Ratio;Counts",int(Energy[i])));

        fitFunc_p[i] = new TF1(Form("fitFunc_p_%d", i), "gaus", h1_p[i]->GetMean()-2*h1_p[i]->GetRMS(), h1_p[i]->GetMean()+2*h1_p[i]->GetRMS()); fitFunc_p[i]->SetLineColor(kRed);
        fitFunc_d[i] = new TF1(Form("fitFunc_d_%d", i), "gaus", h1_d[i]->GetMean()-2*h1_d[i]->GetRMS(), h1_d[i]->GetMean()+2*h1_d[i]->GetRMS()); fitFunc_d[i]->SetLineColor(kBlue);
        fitFunc_h[i] = new TF1(Form("fitFunc_h_%d", i), "gaus", h1_h[i]->GetMean()-1.5*h1_h[i]->GetRMS(), h1_h[i]->GetMean()+1.5*h1_h[i]->GetRMS()); fitFunc_h[i]->SetLineColor(kGreen-3);


        auto c1 = new TCanvas("c1","c1",900,600);
        c1->cd();
        gPad->SetLogy();
        gStyle->SetOptStat(0);
        h1_e[i]->SetTitle(Form("%d GeV Electron Energy Deposit Ratio;Energy Deposit / Incident Kinetic Energy;No. Events",int(Energy[i])));
        h1_e[i]->Draw("hist");
        h1_p[i]->Draw("SAME");
        h1_d[i]->Draw("SAME");
        h1_h[i]->Draw("SAME");

        auto legend1 = new TLegend(0.52, 0.68, 0.68, 0.88);
        legend1->AddEntry(h1_p[i], "Proton", "l");
        legend1->AddEntry(h1_d[i], "Deuteron", "l");
        legend1->AddEntry(h1_e[i], "Electron", "l");
        legend1->AddEntry(h1_h[i], "Helium4", "l");         
        legend1->Draw();       

        h1_p[i]->Fit(fitFunc_p[i],"RQ");
        h1_d[i]->Fit(fitFunc_d[i],"RQ");
        h1_h[i]->Fit(fitFunc_h[i],"RQ");

        Electron_Edep[i]     = h1_e[i]->GetMean();
        Electron_Edep_Err[i] = h1_e[i]->GetRMS();
        fitFunc_p[i]->Draw("same");
        Proton_Edep[i]     = fitFunc_p[i]->GetParameter(1);
        Proton_Edep_Err[i] = fitFunc_p[i]->GetParameter(2);
        fitFunc_d[i]->Draw("same");
        Deuteron_Edep[i]     = fitFunc_d[i]->GetParameter(1);
        Deuteron_Edep_Err[i] = fitFunc_d[i]->GetParameter(2);
        fitFunc_h[i]->Draw("same");
        Helium4_Edep[i]     = fitFunc_h[i]->GetParameter(1);
        Helium4_Edep_Err[i] = fitFunc_h[i]->GetParameter(2);
        c1->SaveAs( Form("/Users/xiongzheng/software/B4/B4c/Script/EnergyDep/EnergyDeposit_%dGeV.pdf",int(Energy[i])) );

    }
    auto c0 = new TCanvas("c0","c0",900,600);
    auto gre_e = new TGraphErrors(19, Energy, Electron_Edep, Energy_Err, Electron_Edep_Err);
    auto gre_p = new TGraphErrors(19, Energy, Proton_Edep, Energy_Err, Proton_Edep_Err);
    auto gre_d = new TGraphErrors(19, Energy, Deuteron_Edep, Energy_Err, Deuteron_Edep_Err);
    auto gre_h = new TGraphErrors(19, Energy, Helium4_Edep, Energy_Err, Helium4_Edep_Err);


    gre_e->SetTitle("Energy Deposit Ratio vs Energy; Kinetic Energy (GeV); Deposit Energy/Incident Energy");
    gre_e->SetMarkerStyle(22);
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

    c0->Clear();
    c0->cd();
    // gPad->SetLogy();
    gPad->SetLogx();

    gre_e->Draw("AP");
    gre_h->Draw("PSAME");
    gre_d->Draw("PSAME");
    gre_p->Draw("PSAME");
    gre_e->GetYaxis()->SetRangeUser(0.1 , 1.05);
    gre_e->GetYaxis()->SetNdivisions(505);
    gre_e->GetYaxis()->SetLabelSize(0.05);
    gre_e->GetYaxis()->SetTitleSize(0.05);
    gre_e->GetYaxis()->SetTitleOffset(0.9);
    gre_e->GetXaxis()->SetLimits(9,1100);


    auto legend1 = new TLegend(0.62, 0.58, 0.88, 0.78);
    legend1->SetNColumns(2);
    legend1->AddEntry(gre_p, "HET Proton", "ep");
    legend1->AddEntry(gre_d, "HET Deuteron", "ep");
    legend1->AddEntry(gre_e, "HET Electron", "ep");
    legend1->AddEntry(gre_h, "HET Helium4", "ep");
    legend1->Draw();

    // c0->SaveAs("/Users/xiongzheng/software/B4/B4c/Script/EnergyDep/EnergyDeposit.pdf");
   
}