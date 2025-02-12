double smartCeil(double value);

void Edep_Ratio()
{
    double Proton_Edep[18]={0};
    double Proton_Edep_Err[18]={0};

    double Electron_Edep[18]={0};
    double Electron_Edep_Err[18]={0};

    double Energy[18]={0};
    double Energy_Err[18]={0};
    TH1D *h1_e[18];  TF1  *fitFunc_e[18];
    TH1D *h1_p[18];  TF1  *fitFunc_p[18];
    TH1D *h1_d[18];  TF1  *fitFunc_d[18];
    TH1D *h1_h[18];  TF1  *fitFunc_h[18];
    for (int i = 0; i < 1; i++)
    {
        if(i<9)  {Energy[i] =  (i+1)*10;}
        else   {Energy[i] =  i*100-800;}
        cout << "Energy = " << int(Energy[i]) << " GeV !" << endl;


        auto proton_file = TFile::Open(Form("/Users/xiongzheng/software/B4/B4c/Root/Proton_%dGeV.root",int(Energy[i])));
        auto proton_tree = (TTree*)proton_file->Get("B4");
        auto deuteron_file = TFile::Open(Form("/Users/xiongzheng/software/B4/B4c/Root/Proton_%dGeV.root",int(Energy[i])));
        auto deuteron_tree = (TTree*)deuteron_file->Get("B4");
        auto electron_file = TFile::Open(Form("/Users/xiongzheng/software/B4/B4c/Root/Proton_%dGeV.root",int(Energy[i])));
        auto electron_tree = (TTree*)electron_file->Get("B4");
        auto helium4_file = TFile::Open(Form("/Users/xiongzheng/software/B4/B4c/Root/Proton_%dGeV.root",int(Energy[i])));
        auto helium4_tree = (TTree*)helium4_file->Get("B4");

        double max_e_TotalE = electron_tree->GetMaximum("Total_E");
        double max_e_Energy = electron_tree->GetMaximum("Energy");
        double max_p_TotalE = proton_tree->GetMaximum("Total_E");
        double max_p_Energy = proton_tree->GetMaximum("Energy");
        double max_d_TotalE = deuteron_tree->GetMaximum("Total_E");
        double max_d_Energy = deuteron_tree->GetMaximum("Energy");
        double max_h_TotalE = helium4_tree->GetMaximum("Total_E");
        double max_h_Energy = helium4_tree->GetMaximum("Energy");
        double ceilmax = max({max_e_TotalE/max_e_Energy, max_p_TotalE/max_p_Energy, max_d_TotalE/max_d_Energy, max_h_TotalE/max_h_Energy});

        h1_p[i] = new TH1D(Form("h1_p[%d]",i),Form("h1_p[%d]",i),100,0,smartCeil(ceilmax)); 
        h1_d[i] = new TH1D(Form("h1_d[%d]",i),Form("h1_d[%d]",i),100,0,smartCeil(ceilmax)); 
        h1_e[i] = new TH1D(Form("h1_e[%d]",i),Form("h1_e[%d]",i),100,0,smartCeil(ceilmax)); 
        h1_h[i] = new TH1D(Form("h1_h[%d]",i),Form("h1_h[%d]",i),100,0,smartCeil(ceilmax)); 

        proton_tree->Draw(Form("Total_E/Energy>>h1_p[%d]",i), "", "");   h1_p[i]->SetLineColor(kRed);      h1_p[i]->SetMarkerColor(kRed);     h1_p[i]->SetLineWidth(2); // h1_p[i]->GetYaxis()->SetRangeUser(0,0.1);
        deuteron_tree->Draw(Form("Total_E/Energy>>h1_d[%d]",i), "", ""); h1_d[i]->SetLineColor(kBlue);     h1_d[i]->SetMarkerColor(kBlue);    h1_d[i]->SetLineWidth(2); // h1_e[i]->GetYaxis()->SetRangeUser(0,0.1);
        electron_tree->Draw(Form("Total_E/Energy>>h1_e[%d]",i), "", ""); h1_e[i]->SetLineColor(kOrange-3); h1_e[i]->SetMarkerColor(kOrange-3);h1_e[i]->SetLineWidth(2); // h1_e[i]->GetYaxis()->SetRangeUser(0,0.1);
        helium4_tree->Draw(Form("Total_E/Energy>>h1_h[%d]",i), "", "");  h1_h[i]->SetLineColor(kGreen-3);  h1_h[i]->SetMarkerColor(kGreen-3); h1_h[i]->SetLineWidth(2); // h1_e[i]->GetYaxis()->SetRangeUser(0,0.1);
        
        h1_e[i]->SetTitle(Form("%d GeV - Deposit Energy/Incident Energy;Energy Deposit Ratio;Counts",int(Energy[i])));

        fitFunc_p[i] = new TF1(Form("fitFunc_p_%d", i), "gaus", h1_p[i]->GetMean()-3*h1_p[i]->GetRMS(), h1_p[i]->GetMean()+3*h1_p[i]->GetRMS());
        fitFunc_d[i] = new TF1(Form("fitFunc_d_%d", i), "gaus", h1_d[i]->GetMean()-3*h1_d[i]->GetRMS(), h1_d[i]->GetMean()+3*h1_d[i]->GetRMS());
        fitFunc_e[i] = new TF1(Form("fitFunc_e_%d", i), "gaus", h1_e[i]->GetMean()-3*h1_e[i]->GetRMS(), h1_e[i]->GetMean()+3*h1_e[i]->GetRMS());
        fitFunc_h[i] = new TF1(Form("fitFunc_h_%d", i), "gaus", h1_h[i]->GetMean()-3*h1_h[i]->GetRMS(), h1_h[i]->GetMean()+3*h1_h[i]->GetRMS());


        auto c1 = new TCanvas("c1","c1",900,600);
        c1->cd();
        gPad->SetLogy();
        gStyle->SetOptStat(0);
        h1_e[i]->Draw();
        h1_p[i]->Draw("same");
        h1_d[i]->Draw("same");
        h1_h[i]->Draw("same");

        auto legend1 = new TLegend(0.72, 0.68, 0.88, 0.88);
        legend1->AddEntry(h1_p[0], "Proton", "l");
        legend1->AddEntry(h1_d[0], "Deuteron", "l");
        legend1->AddEntry(h1_e[0], "Electron", "l");
        legend1->AddEntry(h1_h[0], "Helium4", "l");         
        legend1->Draw();       

        h1_e[i]->SetTitle(Form("%d GeV Electron Energy Deposit Ratio;Energy Deposit / Incident Kinetic Energy;No. Events",int(Energy[i])));
        h1_e[i]->Fit(fitFunc_e[i],"RQ");
        // fitFunc_e[i]->Draw("same");
        Electron_Edep[i]     = fitFunc_e[i]->GetParameter(1);
        Electron_Edep_Err[i] = fitFunc_e[i]->GetParameter(2);
        c1->SaveAs( Form("/Users/xiongzheng/software/B4/B4c/Script/EnergyDep/EnergyDeposit_%dGeV.pdf",int(Energy[i])) );

    }
    auto c0 = new TCanvas("c0","c0",900,600);
    auto gre_e = new TGraphErrors(18, Energy, Electron_Edep, Energy_Err, Electron_Edep_Err);
    gre_e->SetMarkerStyle(22);
    gre_e->SetMarkerColor(kOrange-3);
    gre_e->SetLineColor(kOrange-3);
    gre_e->SetTitle("Energy Deposit Ratio vs Energy; Kinetic Energy (GeV); Energy Deposit Ratio");
    c0->Clear();
    c0->cd();
    gPad->SetLogy();
    gPad->SetLogx();

    gre_e->Draw("AP");
    gre_e->GetYaxis()->SetRangeUser(1e-6 , 1e-3);
    gre_e->GetYaxis()->SetNdivisions(505);
    gre_e->GetYaxis()->SetLabelSize(0.05);
    gre_e->GetYaxis()->SetTitleSize(0.05);
    gre_e->GetYaxis()->SetTitleOffset(0.9);

    auto legend1 = new TLegend(0.7, 0.78, 0.88, 0.88);
    legend1->SetNColumns(2);
    legend1->AddEntry(gre_e, "Electron", "ep");
    legend1->Draw();

    c0->SaveAs("/Users/xiongzheng/software/B4/B4c/Script/EnergyDep/EnergyDeposit.pdf");
   
}

double smartCeil(double value) {
    if (value == 0) return 0.0; // Edge case for zero
    // Determine the order of magnitude
    double order = pow(10, floor(log10(value)));
    // Scale the value to a range where rounding works
    double scaled_value = value / order;
    // Round up to the nearest multiple of 0.05
    double rounded_scaled = ceil(scaled_value * 20) / 20; // 0.05 = 1/20
    // Restore the original scale
    return rounded_scaled * order;
}