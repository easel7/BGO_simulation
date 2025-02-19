void CrossSection()
{
    double Proton_Section[18]={0};
    double Proton_Section_Err[18]={0};

    double Deuteron_Section[18]={0};
    double Deuteron_Section_Err[18]={0};

    double Electron_Section[18]={0};
    double Electron_Section_Err[18]={0};

    double Helium4_Section[18]={0};
    double Helium4_Section_Err[18]={0};

    double Helium3_Section[18]={0};
    double Helium3_Section_Err[18]={0};

    double Carbon_Section[18]={0};
    double Carbon_Section_Err[18]={0};

    double Energy[18]={0};
    double Energy_Err[18]={0};
    double n_BGO = TMath::Na()*7.13/1245.8344; // cm-3
    TH1D *h1_p[18];    TF1  *fitFunc_p[18];
    TH1D *h1_d[18];    TF1  *fitFunc_d[18];
    TH1D *h1_e[18];    TF1  *fitFunc_e[18];
    TH1D *h1_h[18];    TF1  *fitFunc_h[18];
    TH1D *h1_H[18];    TF1  *fitFunc_H[18];
    TH1D *h1_c[18];    TF1  *fitFunc_c[18];

    TCut HET = "(L0_E+L1_E+L2_E>0.23) && (L3_E>0.046)";

    for (int i = 0; i < 18; i++)
    {
        if(i<9)  {Energy[i] =  (i+1)*10;}
        else   {Energy[i] =  i*100-800;}
        cout << "Energy = " << int(Energy[i]) << " GeV !" << endl;

        auto proton_file = TFile::Open(Form("/Users/xiongzheng/software/B4/B4c/Root/Proton_%dGeV.root",int(Energy[i])));
        auto proton_tree = (TTree*)proton_file->Get("B4");
        h1_p[i] = new TH1D(Form("h1_p[%d]",i),Form("h1_p[%d]",i),150,0,150);
        fitFunc_p[i] = new TF1(Form("fitFunc_p[%d]",i), "[0]*exp(-x/[1])", 0, 80);
        fitFunc_p[i]->SetParameters(600, 15); 
        proton_tree->Draw(Form("First_Depth>>h1_p[%d]",i),HET,"");

        auto deuteron_file = TFile::Open(Form("/Users/xiongzheng/software/B4/B4c/Root/Deuteron_%dGeV.root",int(Energy[i])));
        auto deuteron_tree = (TTree*)deuteron_file->Get("B4");
        h1_d[i] = new TH1D(Form("h1_d[%d]",i),Form("h1_d[%d]",i),150,0,150);
        fitFunc_d[i] = new TF1(Form("fitFunc_d[%d]",i), "[0]*exp(-x/[1])", 0, 80);
        fitFunc_d[i]->SetParameters(100, 15); 
        deuteron_tree->Draw(Form("First_Depth>>h1_d[%d]",i), HET, "");

        auto electron_file = TFile::Open(Form("/Users/xiongzheng/software/B4/B4c/Root/Electron_%dGeV.root",int(Energy[i])));
        auto electron_tree = (TTree*)electron_file->Get("B4");
        h1_e[i] = new TH1D(Form("h1_e[%d]",i),Form("h1_e[%d]",i),150,0,150);
        fitFunc_e[i] = new TF1(Form("fitFunc_e[%d]",i), "[0]*exp(-x/[1])", 0, 80);
        fitFunc_e[i]->SetParameters(100, 15); 
        electron_tree->Draw(Form("First_Depth>>h1_e[%d]",i), "", "");

        auto helium4_file = TFile::Open(Form("/Users/xiongzheng/software/B4/B4c/Root/Helium4_%dGeV.root",int(Energy[i])));
        auto helium4_tree = (TTree*)helium4_file->Get("B4");
        h1_h[i] = new TH1D(Form("h1_h[%d]",i),Form("h1_h[%d]",i),150,0,150);
        fitFunc_h[i] = new TF1(Form("fitFunc_h[%d]",i), "[0]*exp(-x/[1])", 0, 80);
        fitFunc_h[i]->SetParameters(100, 15); 
        helium4_tree->Draw(Form("First_Depth>>h1_h[%d]",i), HET, "");

        auto helium3_file = TFile::Open(Form("/Users/xiongzheng/software/B4/B4c/Root/Helium4_%dGeV.root",int(Energy[i])));
        auto helium3_tree = (TTree*)helium3_file->Get("B4");
        h1_H[i] = new TH1D(Form("h1_H[%d]",i),Form("h1_H[%d]",i),150,0,150);
        fitFunc_H[i] = new TF1(Form("fitFunc_H[%d]",i), "[0]*exp(-x/[1])", 0, 80);
        fitFunc_H[i]->SetParameters(100, 15); 
        helium4_tree->Draw(Form("First_Depth>>h1_H[%d]",i), HET, "");

        auto c1 = new TCanvas("c1","c1",2000,1500);
        c1->Clear();
        c1->Divide(3,2);
        gStyle->SetOptFit(1111);
        c1->cd(1);
        proton_file->cd();
        gPad->SetLogy();
        h1_p[i]->Draw("hist");
        h1_p[i]->SetTitle(Form("%d GeV Proton Depth Distribution; Depth (mm); Counts", int(Energy[i])));
        h1_p[i]->Fit(fitFunc_p[i], "R"); // 进行拟合
        fitFunc_p[i]->Draw("same");
        double proton_constant   = fitFunc_p[i]->GetParameter(0);
        double proton_nsigma     = fitFunc_p[i]->GetParameter(1);
        double proton_nsigma_err = fitFunc_p[i]->GetParError(1);
        Proton_Section[i] = 1 / (proton_nsigma * n_BGO) * 1e25; // Convert to barn
        Proton_Section_Err[i] = Proton_Section[i] * proton_nsigma_err / proton_nsigma;
        cout << "Proton " << Energy[i] << " GeV: Sigma = " << Proton_Section[i] << " ± " << Proton_Section_Err[i] << " barn" << endl;

        // Process Deuteron Data
        c1->cd(2);
        deuteron_file->cd();
        gPad->SetLogy();
        h1_d[i]->Draw("hist");
        h1_d[i]->SetTitle(Form("%d GeV Deuteron Depth Distribution; Depth (mm); Counts", int(Energy[i])));
        h1_d[i]->Fit(fitFunc_d[i], "R");
        fitFunc_d[i]->Draw("same");
        double deuteron_constant   = fitFunc_d[i]->GetParameter(0);
        double deuteron_nsigma     = fitFunc_d[i]->GetParameter(1);
        double deuteron_nsigma_err = fitFunc_d[i]->GetParError(1);

        Deuteron_Section[i] = 1 / (deuteron_nsigma * n_BGO) * 1e25;
        Deuteron_Section_Err[i] = Deuteron_Section[i] * deuteron_nsigma_err / deuteron_nsigma;
        cout << "Deuteron " << Energy[i] << " GeV: Sigma = " << Deuteron_Section[i] << " ± " << Deuteron_Section_Err[i] << " barn" << endl;

        c1->cd(3);
        electron_file->cd();
        gPad->SetLogy();
        h1_e[i]->Draw("hist");
        h1_e[i]->SetTitle(Form("%d GeV Electron Depth Distribution; Depth (mm); Counts", int(Energy[i])));
        h1_e[i]->Fit(fitFunc_e[i], "R");
        fitFunc_e[i]->Draw("same");
        double electron_constant   = fitFunc_e[i]->GetParameter(0);
        double electron_nsigma     = fitFunc_e[i]->GetParameter(1);
        double electron_nsigma_err = fitFunc_e[i]->GetParError(1);

        Electron_Section[i] = 1 / (electron_nsigma * n_BGO) * 1e25;
        Electron_Section_Err[i] = Electron_Section[i] * electron_nsigma_err / electron_nsigma;
        cout << "Electron " << Energy[i] << " GeV: Sigma = " << Electron_Section[i] << " ± " << Electron_Section_Err[i] << " barn" << endl;
        
        c1->cd(4);
        helium4_file->cd();
        gPad->SetLogy();
        h1_h[i]->Draw("hist");
        h1_h[i]->SetTitle(Form("%d GeV Helium4 Depth Distribution; Depth (mm); Counts", int(Energy[i])));
        h1_h[i]->Fit(fitFunc_h[i], "R");
        fitFunc_h[i]->Draw("same");
        double helium4_constant   = fitFunc_h[i]->GetParameter(0);
        double helium4_nsigma     = fitFunc_h[i]->GetParameter(1);
        double helium4_nsigma_err = fitFunc_h[i]->GetParError(1);

        Helium4_Section[i] = 1 / (helium4_nsigma * n_BGO) * 1e25;
        Helium4_Section_Err[i] = Helium4_Section[i] * helium4_nsigma_err / helium4_nsigma;
        cout << "Helium4 " << Energy[i] << " GeV: Sigma = " << Helium4_Section[i] << " ± " << Helium4_Section_Err[i] << " barn" << endl;

        c1->cd(5);
        helium3_file->cd();
        gPad->SetLogy();
        h1_H[i]->Draw("hist");
        h1_H[i]->SetTitle(Form("%d GeV Helium3 Depth Distribution; Depth (mm); Counts", int(Energy[i])));
        h1_H[i]->Fit(fitFunc_H[i], "R");
        fitFunc_H[i]->Draw("same");
        double helium3_constant   = fitFunc_H[i]->GetParameter(0);
        double helium3_nsigma     = fitFunc_H[i]->GetParameter(1);
        double helium3_nsigma_err = fitFunc_H[i]->GetParError(1);

        Helium3_Section[i] = 1 / (helium3_nsigma * n_BGO) * 1e25;
        Helium3_Section_Err[i] = Helium3_Section[i] * helium3_nsigma_err / helium3_nsigma;
        cout << "Helium4 " << Energy[i] << " GeV: Sigma = " << Helium3_Section[i] << " ± " << Helium3_Section_Err[i] << " barn" << endl;


        c1->SaveAs( Form("/Users/xiongzheng/software/B4/B4c/Script/CrossS/CrossSection_%dGeV.pdf",int(Energy[i])) );
    }
    
    auto c0 = new TCanvas("c0","c0",1200,1200);
    auto gre_p = new TGraphErrors(18, Energy, Proton_Section, Energy_Err, Proton_Section_Err);
    gre_p->SetTitle("Fitted Cross Section vs Energy; Kinetic Energy (GeV); Cross Section (barn)");
    gre_p->SetMarkerStyle(20);
    gre_p->SetMarkerColor(kRed);
    gre_p->SetLineColor(kRed);

    auto gre_d = new TGraphErrors(18, Energy, Deuteron_Section, Energy_Err, Deuteron_Section_Err);
    gre_d->SetTitle("; Kinetic Energy (GeV); Cross Section (barn)");
    gre_d->SetMarkerStyle(21);
    gre_d->SetMarkerColor(kBlue);
    gre_d->SetLineColor(kBlue);

    auto gre_e = new TGraphErrors(18, Energy, Electron_Section, Energy_Err, Electron_Section_Err);
    gre_e->SetMarkerStyle(22);
    gre_e->SetMarkerColor(kOrange-3);
    gre_e->SetLineColor(kOrange-3);

    auto gre_h = new TGraphErrors(18, Energy, Helium4_Section, Energy_Err, Helium4_Section_Err);
    gre_h->SetMarkerStyle(23);
    gre_h->SetMarkerColor(kGreen-3);
    gre_h->SetLineColor(kGreen-3);

    auto gre_H = new TGraphErrors(18, Energy, Helium3_Section, Energy_Err, Helium3_Section_Err);
    gre_H->SetMarkerStyle(32);
    gre_H->SetMarkerColor(kGreen-3);
    gre_H->SetLineColor(kGreen-3);

    c0->Clear();
    c0->cd();
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.5, 1, 1.0);
    pad1->SetBottomMargin(0); // Upper and lower plot are joined
    pad1->SetGrid(1, 1);      // Vertical ,Horizontal grid
    pad1->SetLogy(0);
    pad1->SetLogx(1);
    pad1->Draw();             // Draw the upper pad: pad1
    pad1->cd();               // pad1 becomes the current pad
    gre_p->Draw("AP");
    gre_p->GetYaxis()->SetRangeUser(100, 3250);
    gre_p->GetYaxis()->SetNdivisions(505);
    gre_p->GetYaxis()->SetLabelSize(0.05);
    gre_p->GetYaxis()->SetTitleSize(0.07);
    gre_p->GetYaxis()->SetTitleOffset(0.5);

    gre_d->Draw("PSAME");
    gre_e->Draw("PSAME");
    gre_h->Draw("PSAME");
    gre_H->Draw("PSAME");

    auto legend1 = new TLegend(0.60, 0.68, 0.88, 0.88);
    legend1->SetNColumns(2);
    legend1->AddEntry(gre_p, "Proton", "ep");
    legend1->AddEntry(gre_d, "Deuteron", "ep");
    legend1->AddEntry(gre_e, "Electron", "ep");
    legend1->AddEntry(gre_h, "Helium4", "ep");
    legend1->AddEntry(gre_H, "Helium3", "ep");

    legend1->Draw();

    c0->cd();
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.0, 1, 0.5);
    pad2->SetTopMargin(0); 
    pad2->SetBottomMargin(0.2);
    pad2->SetGrid(1, 1);      // Vertical ,Horizontal grid
    pad2->SetLogy(0);
    pad2->SetLogx(1);
    pad2->Draw();
    pad2->cd();       // pad2 becomes the current pad
    gre_d->Draw("AP");
    gre_d->GetYaxis()->SetRangeUser(182, 204);
    gre_d->GetYaxis()->SetNdivisions(505);
    gre_d->GetYaxis()->SetLabelSize(0.05);
    gre_d->GetYaxis()->SetTitleSize(0.07);
    gre_d->GetYaxis()->SetTitleOffset(0.5);

    gre_d->GetXaxis()->SetLabelSize(0.06);
    gre_d->GetXaxis()->SetTitleSize(0.07);


    gre_p->Draw("PSAME");

    auto legend2 = new TLegend(0.75, 0.22, 0.88, 0.42);
    legend2->AddEntry(gre_p, "Proton", "ep");
    legend2->AddEntry(gre_d, "Deuteron", "ep");
    legend2->Draw();


    c0->SaveAs("/Users/xiongzheng/software/B4/B4c/Script/CrossS/CrossSection.pdf");


}