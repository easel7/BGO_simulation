void Edep_Ratio_SingleLayer()
{
    auto proton_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Proton_100GeV.root");
    auto proton_tree = (TTree*)proton_file->Get("B4");
    auto deuteron_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Deuteron_100GeV.root");
    auto deuteron_tree = (TTree*)deuteron_file->Get("B4");
    auto electron_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Electron_100GeV.root");
    auto electron_tree = (TTree*)electron_file->Get("B4");
    auto helium4_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Helium4_100GeV.root");
    auto helium4_tree = (TTree*)helium4_file->Get("B4");

    TCut UBT = "L0_E+L1_E>0.0092";
    TCut HET = "(L0_E+L1_E+L2_E>0.23) && (L3_E>0.046)";

    auto h1_p = new TH1D("h1_p","h1_p",50,-5,0);  
    auto h1_d = new TH1D("h1_d","h1_d",50,-5,0);  
    auto h1_e = new TH1D("h1_e","h1_e",50,-5,0);  
    auto h1_h = new TH1D("h1_h","h1_h",50,-5,0);  

    proton_tree->Draw("log10(L0_E/Total_E)>>h1_p",HET,"");
    deuteron_tree->Draw("log10(L0_E/Total_E)>>h1_d",HET,"");
    electron_tree->Draw("log10(L0_E/Total_E)>>h1_e",HET,"");
    helium4_tree->Draw("log10(L0_E/Total_E)>>h1_h",HET,"");

    h1_p->Scale(1.0/h1_p->Integral());h1_p->SetLineColor(kRed);     h1_p->SetMarkerColor(kRed);     h1_p->SetLineWidth(2);h1_p->GetYaxis()->SetRangeUser(0,0.25);h1_p->SetTitle("100 GeV incident EdepRatio Distrubution in L0;log_{10}(Energy Deposit in Layer/ Total Deposit);Normalized Count");
    h1_d->Scale(1.0/h1_d->Integral());h1_d->SetLineColor(kBlue);    h1_d->SetMarkerColor(kBlue);    h1_d->SetLineWidth(2);
    h1_e->Scale(1.0/h1_e->Integral());h1_e->SetLineColor(kOrange-3);h1_e->SetMarkerColor(kOrange-3);h1_e->SetLineWidth(2);
    h1_h->Scale(1.0/h1_h->Integral());h1_h->SetLineColor(kGreen-3); h1_h->SetMarkerColor(kGreen-3); h1_h->SetLineWidth(2);

    cout << h1_d->GetMean() << " , " << h1_d->GetRMS() << endl;

    TF1  *fitFunc_p = new TF1("fitFunc_p","[0]/(-x*[2]*TMath::Sqrt(2*TMath::Pi()))*TMath::Exp(-0.5*TMath::Power(TMath::Log10(-x)-[1],2)/TMath::Power([2],2))", h1_p->GetMean()-3*h1_p->GetRMS(),0); fitFunc_p->SetParameters(0.1, -h1_p->GetBinCenter(h1_p->GetMaximumBin()), 0.5); fitFunc_p->SetLineColor(kRed);     
    TF1  *fitFunc_d = new TF1("fitFunc_d","[0]/(-x*[2]*TMath::Sqrt(2*TMath::Pi()))*TMath::Exp(-0.5*TMath::Power(TMath::Log10(-x)-[1],2)/TMath::Power([2],2))", h1_d->GetMean()-3*h1_d->GetRMS(),0); fitFunc_d->SetParameters(0.1, -h1_d->GetBinCenter(h1_d->GetMaximumBin()), 0.5); fitFunc_d->SetLineColor(kBlue);    
    TF1  *fitFunc_e = new TF1("fitFunc_e","[0]/(-x*[2]*TMath::Sqrt(2*TMath::Pi()))*TMath::Exp(-0.5*TMath::Power(TMath::Log10(-x)-[1],2)/TMath::Power([2],2))", h1_e->GetMean()-3*h1_e->GetRMS(),0); fitFunc_e->SetParameters(0.1, -h1_e->GetBinCenter(h1_e->GetMaximumBin()), 0.5); fitFunc_e->SetLineColor(kOrange-3);
    TF1  *fitFunc_h = new TF1("fitFunc_h","[0]/(-x*[2]*TMath::Sqrt(2*TMath::Pi()))*TMath::Exp(-0.5*TMath::Power(TMath::Log10(-x)-[1],2)/TMath::Power([2],2))", h1_h->GetMean()-3*h1_h->GetRMS(),0); fitFunc_h->SetParameters(0.1, -h1_h->GetBinCenter(h1_h->GetMaximumBin()), 0.5); fitFunc_h->SetLineColor(kGreen-3); 

    auto c1 = new TCanvas("c1","c1",900,600);
    c1->cd();
    c1->Clear();
    h1_p->Draw();
    h1_d->Draw("same");
    h1_e->Draw("same");
    h1_h->Draw("same");

    double quantiles[3] = {0.16, 0.50, 0.84};  // Percentiles
    double p_values[3];  // Will store the x-values corresponding to the percentiles
    double d_values[3];  // Will store the x-values corresponding to the percentiles
    double e_values[3];  // Will store the x-values corresponding to the percentiles
    double h_values[3];  // Will store the x-values corresponding to the percentiles

    h1_p->GetQuantiles(3, p_values, quantiles);
    h1_d->GetQuantiles(3, d_values, quantiles);
    h1_e->GetQuantiles(3, e_values, quantiles);
    h1_h->GetQuantiles(3, h_values, quantiles);

    TLine *l_p[3];
    TLine *l_d[3];
    TLine *l_e[3];
    TLine *l_h[3];

    for (int ii = 0 ;ii< 3 ; ii++)
    {
        l_p[ii] = new TLine(p_values[ii],0,p_values[ii],h1_p->GetBinContent(h1_p->FindBin(p_values[ii])));l_p[ii]->SetLineColor(kRed);     l_p[ii]->SetLineWidth(2);l_p[ii]->Draw();
        l_d[ii] = new TLine(d_values[ii],0,d_values[ii],h1_d->GetBinContent(h1_d->FindBin(d_values[ii])));l_d[ii]->SetLineColor(kBlue);    l_d[ii]->SetLineWidth(2);l_d[ii]->Draw();
        l_e[ii] = new TLine(e_values[ii],0,e_values[ii],h1_e->GetBinContent(h1_e->FindBin(e_values[ii])));l_e[ii]->SetLineColor(kOrange-3);l_e[ii]->SetLineWidth(2);l_e[ii]->Draw();
        l_h[ii] = new TLine(h_values[ii],0,h_values[ii],h1_h->GetBinContent(h1_h->FindBin(h_values[ii])));l_h[ii]->SetLineColor(kGreen-3); l_h[ii]->SetLineWidth(2);l_h[ii]->Draw();
    }

    auto legend1 = new TLegend(0.12, 0.68, 0.28, 0.88);
    legend1->AddEntry(h1_p, "Proton", "el");
    legend1->AddEntry(h1_d, "Deuteron", "el");
    legend1->AddEntry(h1_e, "Electron", "el");
    legend1->AddEntry(h1_h, "Helium4", "el");         
    legend1->Draw();       

    auto c2 = new TCanvas("c2","c2",900,600);
    c2->cd();
    c2->Clear();

    h1_p->Draw();
    h1_d->Draw("same");
    h1_e->Draw("same");
    h1_h->Draw("same");

    h1_p->Fit(fitFunc_p,"RQ");
    h1_d->Fit(fitFunc_d,"R");
    h1_e->Fit(fitFunc_e,"RQ");
    h1_h->Fit(fitFunc_h,"RQ");

    legend1->Draw();       

    c1->SaveAs("/Users/xiongzheng/software/B4/B4c/Script/EnergyDep/Edep_Ratio_SingleLayer_logNormal.pdf");
    c1->SaveAs("/Users/xiongzheng/software/B4/B4c/Script/EnergyDep/Edep_Ratio_SingleLayer_16_50_84.pdf");

}