void test()
{
    auto proton_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Proton_PowerLaw.root");
    auto proton_tree = (TTree*)proton_file->Get("B4");
    auto deuteron_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Deuteron_PowerLaw.root");
    auto deuteron_tree = (TTree*)deuteron_file->Get("B4");
    auto electron_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Electron_PowerLaw.root");
    auto electron_tree = (TTree*)electron_file->Get("B4");
    auto helium4_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Helium4_PowerLaw.root");
    auto helium4_tree = (TTree*)helium4_file->Get("B4");
    
    auto *h2_p = new TH2D("h2_p","h2_p",40,0,4000,40,0,4000);
    auto *h2_d = new TH2D("h2_d","h2_d",40,0,4000,40,0,4000);
    auto *h2_e = new TH2D("h2_e","h2_e",40,0,4000,40,0,4000);
    auto *h2_h = new TH2D("h2_h","h2_h",40,0,4000,40,0,4000);

    proton_tree->Draw("Total_E:Energy>>h2_p","","");   
    deuteron_tree->Draw("Total_E:Energy>>h2_d","",""); 
    electron_tree->Draw("Total_E:Energy>>h2_e","",""); 
    helium4_tree->Draw("Total_E:Energy>>h2_h","","");  

    auto c1 = new TCanvas("c1","c1",1200,1200);
    h2_p->Draw("colz");

    // h2_p->Scale(1.0/h2_p->Integral());h2_p->SetLineColor(kRed);     h2_p->SetMarkerColor(kRed);     h2_p->SetLineWidth(2);
    // h2_p->GetYaxis()->SetRangeUser(0,0.1);h2_p->SetTitle("EdepRatio Distrubution in L%d;log_{10}(Energy Deposit Ratio);Normalized Count",j));
    // h2_d->Scale(1.0/h2_d->Integral());h2_d->SetLineColor(kBlue);    h2_d->SetMarkerColor(kBlue);    h2_d->SetLineWidth(2);
    // h2_e->Scale(1.0/h2_e->Integral());h2_e->SetLineColor(kOrange-3);h2_e->SetMarkerColor(kOrange-3);h2_e->SetLineWidth(2);
    // h2_h->Scale(1.0/h2_h->Integral());h2_h->SetLineColor(kGreen-3); h2_h->SetMarkerColor(kGreen-3); h2_h->SetLineWidth(2);

  


}