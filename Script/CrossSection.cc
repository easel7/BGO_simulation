void CrossSection()
{

    double Proton_Section[9]={0};
    double Proton_Section_Err[9]={0};

    double Deuteron_Section[9]={0};
    double Deuteron_Section_Err[9]={0};

    double Energy[9]={0};
    double Energy_Err[9]={0};
    double n_BGO = TMath::Na()*7.13/1245.8344; // cm-3
    TH1D *h1_p[9];
    TH1D *h1_d[9];

    auto c0 = new TCanvas("c0","c0",900,600);
    auto fitFunc = new TF1("fitFunc", "[0]*exp(-x/[1])", 0, 150);
    auto c1 = new TCanvas("c1","c1",2700,600);
    c1->Divide(9,2);

    for (int i = 0; i < 1; i++)
    {
        Energy[i] =  (i+1)*10;
        cout << int(Energy[i]) << endl;


        auto proton_file = TFile::Open(Form("/Users/xiongzheng/software/B4/B4c/Root/Proton_%dGeV.root",int(Energy[i])));
        auto proton_tree = (TTree*)proton_file->Get("B4");
        h1_p[i] = new TH1D(Form("h1_p[%d]",i),Form("h1_p[%d]",i),150,0,150);

        auto deuteron_file = TFile::Open(Form("/Users/xiongzheng/software/B4/B4c/Root/Deuteron_%dGeV.root",int(Energy[i])));
        auto deuteron_tree = (TTree*)proton_file->Get("B4");
        h1_d[i] = new TH1D(Form("h1_d[%d]",i),Form("h1_d[%d]",i),150,0,150);

        proton_file->cd();
        proton_tree->Draw(Form("First_Depth>>h1_p[%d]",i),"","");
        h1_p[i]->SetTitle("Proton Depth Distribution; Depth (mm); Counts");
        gPad->SetLogy();
        fitFunc->SetParameters(600, 15); // 初始参数：振幅=100, λ=10 cm
        h1_p[i]->Fit(fitFunc, "R"); // 进行拟合
        double proton_constant = fitFunc->GetParameter(0);
        double proton_nsigma = fitFunc->GetParameter(1);
        double proton_nsigma_err = fitFunc->GetParError(1);

        Proton_Section[i] = 1 / (proton_nsigma * n_BGO) * 1e24; // Convert to barn
        Proton_Section_Err[i] = 1 / (proton_nsigma * n_BGO) * 1e24 * proton_nsigma_err / proton_nsigma;
        cout << "Proton " << Energy[i] << " GeV: Sigma = " << Proton_Section[i] << " ± " << Proton_Section_Err[i] << " barn" << endl;

        // // Process Deuteron Data
        // c1->cd(i+1);
        // deuteron_file->cd();
        // deuteron_tree->Draw("First_Depth>>h1_d[i]", "", "");
        // h1_d[i]->SetTitle("Deuteron Depth Distribution; Depth (mm); Counts");
        // gPad->SetLogy();

        // h1_d[i]->Fit(fitFunc, "R");

        // double deuteron_constant = fitFunc->GetParameter(0);
        // double deuteron_nsigma = fitFunc->GetParameter(1);
        // double deuteron_nsigma_err = fitFunc->GetParError(1);

        // Deuteron_Section[i] = 1 / (deuteron_nsigma * n_BGO) * 1e24;
        // Deuteron_Section_Err[i] = Deuteron_Section[i] * deuteron_nsigma_err / deuteron_nsigma;

        // cout << "Deuteron " << Energy[i] << " GeV: Sigma = " << Deuteron_Section[i] << " ± " << Deuteron_Section_Err[i] << " barn" << endl;

    }
    
    // c0->cd();
    // gPad->SetLogy(0);
    // auto gre_p = new TGraphErrors(9, Energy, Proton_Section, Energy_Err, Proton_Section_Err);
    // auto gre_d = new TGraphErrors(9, Energy, Deuteron_Section, Energy_Err, Deuteron_Section_Err);

    // gre_p->SetMarkerStyle(20);
    // gre_p->SetMarkerColor(kRed);
    // gre_p->SetTitle("Cross Section vs Energy; Energy (GeV); Cross Section (barn)");
    // gre_d->SetMarkerStyle(21);
    // gre_d->SetMarkerColor(kBlue);

    // gre_p->Draw("AP");
    // gre_d->Draw("PAME");


    // auto legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    // legend->AddEntry(gre_p, "Proton", "p");
    // legend->AddEntry(gre_d, "Deuteron", "p");
    // legend->Draw();
    // c0->SaveAs("/Users/xiongzheng/software/B4/B4c/Script/CrossSection.pdf");


}