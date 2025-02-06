void CrossSection_Single()
{
    auto proton_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Electron_100GeV.root");
    auto proton_tree = (TTree*)proton_file->Get("B4");
    auto c1 = new TCanvas("c1","c1",900,600);
    auto *h0 = new TH1D("h0","h0",150,0,150);
    c1->cd();
    proton_tree->Draw("First_Depth>>h0","","");
    h0->SetTitle("100 GeV Electron - Depth Distribution;Depth(mm);Counts");
    gPad->SetLogy();
    gStyle->SetOptFit(1111);
    TF1 *fitFunc = new TF1("fitFunc", "[0]*exp(-x/[1])", 0, 150);
    fitFunc->SetParameters(100, 10); // 初始参数：振幅=100, λ=10 cm
    h0->Fit(fitFunc, "R"); // 进行拟合
    double constant   = fitFunc->GetParameter(0);
    double nsigma     = fitFunc->GetParameter(1);
    double nsigma_err = fitFunc->GetParError(1);

    cout << "Constant: " << constant  << ", N * Sigma: " << nsigma << " err = " << nsigma_err << endl;

    double n_BGO = TMath::Na()*7.13/1245.8344; // cm-3
    double section = 1 / nsigma / n_BGO * 1e24; // barn
    double section_err = 1 / nsigma / n_BGO * 1e24 * nsigma_err/nsigma; // barn

    TLatex latex;
    latex.SetTextSize(0.04);
    latex.SetTextFont(72);

    latex.SetTextAlign(13);  //align at top
    latex.DrawLatex(40,100,"Fitting Function: P=[0]*exp(-x/[1])");
    
    cout << "Section : " << section << " ± " << section_err << " barn" << endl;
    c1->SaveAs("CrossSection_Single_Electron.pdf");
}