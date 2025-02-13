void test()
{
    auto proton_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Proton.root");
    auto proton_tree = (TTree*)proton_file->Get("B4");
    auto deuteron_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Deuteron.root");
    auto deuteron_tree = (TTree*)deuteron_file->Get("B4");
    auto electron_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Electron.root");
    auto electron_tree = (TTree*)electron_file->Get("B4");
    auto helium4_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Helium4.root");
    auto helium4_tree = (TTree*)helium4_file->Get("B4");
    
    TH2D *h2_p = new TH2D("h2_p","h2_p",100,0,1000,100,0,1000);
    TH2D *h2_d = new TH2D("h2_d","h2_d",100,0,1000,100,0,1000);
    TH2D *h2_e = new TH2D("h2_e","h2_e",100,0,1000,100,0,1000);
    TH2D *h2_h = new TH2D("h2_h","h2_h",100,0,1000,100,0,1000);


    proton_tree->Draw(Form("log10(L%d_E/Total_E)>>h1_p[%d]",j,j),"","");   
    deuteron_tree->Draw(Form("log10(L%d_E/Total_E)>>h1_d[%d]",j,j),"",""); 
    electron_tree->Draw(Form("log10(L%d_E/Total_E)>>h1_e[%d]",j,j),"",""); 
    helium4_tree->Draw(Form("log10(L%d_E/Total_E)>>h1_h[%d]",j,j),"","");  

    h1_p[j]->Scale(1.0/h1_p[j]->Integral());h1_p[j]->SetLineColor(kRed);     h1_p[j]->SetMarkerColor(kRed);     h1_p[j]->SetLineWidth(2);
    h1_p[j]->GetYaxis()->SetRangeUser(0,0.1);h1_p[j]->SetTitle(Form("EdepRatio Distrubution in L%d;log_{10}(Energy Deposit Ratio);Normalized Count",j));
    h1_d[j]->Scale(1.0/h1_d[j]->Integral());h1_d[j]->SetLineColor(kBlue);    h1_d[j]->SetMarkerColor(kBlue);    h1_d[j]->SetLineWidth(2);
    h1_e[j]->Scale(1.0/h1_e[j]->Integral());h1_e[j]->SetLineColor(kOrange-3);h1_e[j]->SetMarkerColor(kOrange-3);h1_e[j]->SetLineWidth(2);
    h1_h[j]->Scale(1.0/h1_h[j]->Integral());h1_h[j]->SetLineColor(kGreen-3); h1_h[j]->SetMarkerColor(kGreen-3); h1_h[j]->SetLineWidth(2);

  


}