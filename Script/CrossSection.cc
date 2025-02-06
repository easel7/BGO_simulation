void CrossSection()
{

    double Proton_Section[18]={0};
    double Proton_Section_Err[18]={0};

    double Deuteron_Section[18]={0};
    double Deuteron_Section_Err[18]={0};

    double Energy[18]={0};
    double Energy_Err[18]={0};
    double n_BGO = TMath::Na()*7.13/1245.8344; // cm-3
    TH1D *h1_p[18];
    TH1D *h1_d[18];
    TF1  *fitFunc_p[18];
    TF1  *fitFunc_d[18];

    auto c0 = new TCanvas("c0","c0",900,600);
    auto c1 = new TCanvas("c1","c1",1800,1800);
    c1->Clear();
    c1->Divide(6,6);

    for (int i = 0; i < 18; i++)
    {
        if(i<9)  {Energy[i] =  (i+1)*10;}
        else   {Energy[i] =  i*100-800;}
        cout << "Energy = " << int(Energy[i]) << " GeV !" << endl;

        auto proton_file = TFile::Open(Form("/Users/xiongzheng/software/B4/B4c/Root/Proton_%dGeV.root",int(Energy[i])));
        auto proton_tree = (TTree*)proton_file->Get("B4");
        h1_p[i] = new TH1D(Form("h1_p[%d]",i),Form("h1_p[%d]",i),150,0,150);
        fitFunc_p[i] = new TF1(Form("fitFunc_p[%d]",i), "[0]*exp(-x/[1])", 0, 150);
        fitFunc_p[i]->SetParameters(600, 15); 
        proton_tree->Draw(Form("First_Depth>>h1_p[%d]",i),"","");

        auto deuteron_file = TFile::Open(Form("/Users/xiongzheng/software/B4/B4c/Root/Deuteron_%dGeV.root",int(Energy[i])));
        auto deuteron_tree = (TTree*)deuteron_file->Get("B4");
        h1_d[i] = new TH1D(Form("h1_d[%d]",i),Form("h1_d[%d]",i),150,0,150);
        fitFunc_d[i] = new TF1(Form("fitFunc_d[%d]",i), "[0]*exp(-x/[1])", 0, 150);
        fitFunc_d[i]->SetParameters(600, 15); 
        deuteron_tree->Draw(Form("First_Depth>>h1_d[%d]",i), "", "");

        c1->cd(i+1);
        // proton_file->cd();
        gPad->SetLogy();
        // h1_p[i]->Draw("hist");
        // h1_p[i]->SetTitle("Proton Depth Distribution; Depth (mm); Counts");
        // h1_p[i]->Fit(fitFunc_p[i], "R"); // 进行拟合
        // double proton_constant   = fitFunc_p[i]->GetParameter(0);
        // double proton_nsigma     = fitFunc_p[i]->GetParameter(1);
        // double proton_nsigma_err = fitFunc_p[i]->GetParError(1);
        // Proton_Section[i] = 1 / (proton_nsigma * n_BGO) * 1e24; // Convert to barn
        // Proton_Section_Err[i] = Proton_Section[i] * proton_nsigma_err / proton_nsigma;
        // cout << "Proton " << Energy[i] << " GeV: Sigma = " << Proton_Section[i] << " ± " << Proton_Section_Err[i] << " barn" << endl;

        // Process Deuteron Data
        c1->cd(i+18);
        // deuteron_file->cd();
        gPad->SetLogy();
        // h1_d[i]->Draw("hist");
        // h1_d[i]->SetTitle("Deuteron Depth Distribution; Depth (mm); Counts");
        // h1_d[i]->Fit(fitFunc_d[i], "R");

        // double deuteron_constant   = fitFunc_d[i]->GetParameter(0);
        // double deuteron_nsigma     = fitFunc_d[i]->GetParameter(1);
        // double deuteron_nsigma_err = fitFunc_d[i]->GetParError(1);

        // Deuteron_Section[i] = 1 / (deuteron_nsigma * n_BGO) * 1e24;
        // Deuteron_Section_Err[i] = Deuteron_Section[i] * deuteron_nsigma_err / deuteron_nsigma;

        // cout << "Deuteron " << Energy[i] << " GeV: Sigma = " << Deuteron_Section[i] << " ± " << Deuteron_Section_Err[i] << " barn" << endl;

    }
    

    // auto gre_p = new TGraphErrors(18, Energy, Proton_Section, Energy_Err, Proton_Section_Err);
    // gre_p->SetTitle("Fitted Cross Section vs Energy; Kinetic Energy (GeV); Cross Section (barn)");
    // gre_p->SetMarkerStyle(20);
    // gre_p->SetMarkerColor(kRed);
    // gre_p->SetLineColor(kRed);


    // auto gre_d = new TGraphErrors(18, Energy, Deuteron_Section, Energy_Err, Deuteron_Section_Err);
    // gre_d->SetMarkerStyle(21);
    // gre_d->SetMarkerColor(kBlue);
    // gre_d->SetLineColor(kBlue);

    // c0->cd();
    // gPad->SetLogy(0);
    // gPad->SetLogx(1);

    // gre_p->Draw("AP");
    // gre_d->Draw("PSAME");

    // auto legend = new TLegend(0.7, 0.8, 0.9, 0.9);
    // legend->AddEntry(gre_p, "Proton", "ep");
    // legend->AddEntry(gre_d, "Deuteron", "ep");
    // legend->Draw();
    // c0->SaveAs("/Users/xiongzheng/software/B4/B4c/Script/CrossSection.pdf");


}