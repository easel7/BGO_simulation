void test()
{
    auto proton_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Proton_400GeV.root");
    auto proton_tree = (TTree*)proton_file->Get("B4");
    auto deuteron_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Deuteron_400GeV.root");
    auto deuteron_tree = (TTree*)deuteron_file->Get("B4");
    auto electron_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Electron_400GeV.root");
    auto electron_tree = (TTree*)electron_file->Get("B4");
    auto helium4_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Helium4_400GeV.root");
    auto helium4_tree = (TTree*)helium4_file->Get("B4");
    
    TH1D *h1_p[14];  TF1  *fitFunc_p[14];
    TH1D *h1_d[14];  TF1  *fitFunc_d[14];
    TH1D *h1_e[14];  TF1  *fitFunc_e[14];
    TH1D *h1_h[14];  TF1  *fitFunc_h[14];

    for (int j = 8; j < 9; j++) // Sub Fig
    {          
        h1_p[j] = new TH1D(Form("h1_p[%d]",j), Form("h1_p[%d]",j),100,-10,0);  
        h1_d[j] = new TH1D(Form("h1_d[%d]",j), Form("h1_d[%d]",j),100,-10,0);  
        h1_e[j] = new TH1D(Form("h1_e[%d]",j), Form("h1_e[%d]",j),100,-10,0);  
        h1_h[j] = new TH1D(Form("h1_h[%d]",j), Form("h1_h[%d]",j),100,-10,0);  

        proton_tree->Draw(Form("log10(L%d_E/Total_E)>>h1_p[%d]",j,j),"","");   h1_p[j]->Scale(1.0/h1_p[j]->Integral());h1_p[j]->SetLineColor(kRed);     h1_p[j]->SetMarkerColor(kRed);     h1_p[j]->SetLineWidth(2);h1_p[j]->GetYaxis()->SetRangeUser(0,0.1);h1_p[j]->SetTitle(Form("EdepRatio Distrubution in L%d;log_{10}(Energy Deposit Ratio);Normalized Count",j));
        deuteron_tree->Draw(Form("log10(L%d_E/Total_E)>>h1_d[%d]",j,j),"",""); h1_d[j]->Scale(1.0/h1_d[j]->Integral());h1_d[j]->SetLineColor(kBlue);    h1_d[j]->SetMarkerColor(kBlue);    h1_d[j]->SetLineWidth(2);
        electron_tree->Draw(Form("log10(L%d_E/Total_E)>>h1_e[%d]",j,j),"",""); h1_e[j]->Scale(1.0/h1_e[j]->Integral());h1_e[j]->SetLineColor(kOrange-3);h1_e[j]->SetMarkerColor(kOrange-3);h1_e[j]->SetLineWidth(2);
        helium4_tree->Draw(Form("log10(L%d_E/Total_E)>>h1_h[%d]",j,j),"","");  h1_h[j]->Scale(1.0/h1_h[j]->Integral());h1_h[j]->SetLineColor(kGreen-3); h1_h[j]->SetMarkerColor(kGreen-3); h1_h[j]->SetLineWidth(2);
        
        // auto c2 = new TCanvas("c2","c2",1000,1000);
        auto f1 = new TF1("f1","[0]/(-x*[2]*TMath::Sqrt(2*TMath::Pi()))*TMath::Exp(-0.5*TMath::Power(TMath::Log10(-x)-[1],2)/TMath::Power([2],2))", -4, 0);
        f1->SetParameters(1, 0, 0.25); // Example values for the parameters
        h1_p[j]->Draw();
        h1_d[j]->Draw("same");
        h1_e[j]->Draw("same");
        h1_h[j]->Draw("same");
        h1_p[j]->Fit(f1,"R");
        // h1_d[j]->Fit(f1,"R");
        // h1_e[j]->Fit(f1,"R");
        // h1_h[j]->Fit(f1,"R");


    }
  


}