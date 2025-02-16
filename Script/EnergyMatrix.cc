void EnergyMatrix()
{
    auto proton_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Proton_PowerLaw.root");
    auto proton_tree = (TTree*)proton_file->Get("B4");
    auto deuteron_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Deuteron_PowerLaw.root");
    auto deuteron_tree = (TTree*)deuteron_file->Get("B4");
    auto electron_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Electron_PowerLaw.root");
    auto electron_tree = (TTree*)electron_file->Get("B4");
    auto helium4_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Helium4_PowerLaw.root");
    auto helium4_tree = (TTree*)helium4_file->Get("B4");
    
    TCut UBT = "(L0_E+L1_E+L2_E>0.23) && (L3_E>0.046)";


    auto *h2_p = new TH2D("h2_p","h2_p",26,1,3.6,26,1,3.6); auto *h1_p = new TH2D("h1_p","h1_p",26,1,3.6,26,1,3.6);
    auto *h2_d = new TH2D("h2_d","h2_d",26,1,3.6,26,1,3.6); auto *h1_d = new TH2D("h1_d","h1_d",26,1,3.6,26,1,3.6);
    auto *h2_e = new TH2D("h2_e","h2_e",26,1,3.6,26,1,3.6); auto *h1_e = new TH2D("h1_e","h1_e",26,1,3.6,26,1,3.6);
    auto *h2_h = new TH2D("h2_h","h2_h",26,1,3.6,26,1,3.6); auto *h1_h = new TH2D("h1_h","h1_h",26,1,3.6,26,1,3.6);

    proton_tree->Draw("log10(Total_E):log10(Energy)>>h2_p",UBT,"");   
    deuteron_tree->Draw("log10(Total_E):log10(Energy)>>h2_d",UBT,""); 
    electron_tree->Draw("log10(Total_E):log10(Energy)>>h2_e",UBT,""); 
    helium4_tree->Draw("log10(Total_E):log10(Energy)>>h2_h",UBT,"");  
    auto tex = new TLatex(3.4,3.7,"log_{10} Entries");
    tex->SetTextSize(0.03);
    for (int ii=0;ii<26;ii++)
    {
        for(int jj=0;jj<26;jj++)
        {
            h1_p->SetBinContent(ii,jj,log10(h2_p->GetBinContent(ii,jj)));
            h1_d->SetBinContent(ii,jj,log10(h2_d->GetBinContent(ii,jj)));
            h1_e->SetBinContent(ii,jj,log10(h2_e->GetBinContent(ii,jj)));
            h1_h->SetBinContent(ii,jj,log10(h2_h->GetBinContent(ii,jj)));
        }
    }

    auto c1 = new TCanvas("c1","c1",1600,1600);
    
    c1->Divide(2,2);
    c1->cd(1);
    // gPad->SetLogz();  // 设置 Z 轴为对数刻度
    gStyle->SetOptStat(0);
    h1_p->SetTitle("Proton Energy Response Matrix;log_{10}Energy Incident(GeV);log_{10}Energy Deposit(GeV)");
    h1_p->Draw("colz");
    tex->Draw();

    c1->cd(2);
    // gPad->SetLogz();  // 设置 Z 轴为对数刻度
    gStyle->SetOptStat(0);
    h1_d->SetTitle("Deuteron Energy Response Matrix;log_{10}Energy Incident(GeV);log_{10}Energy Deposit(GeV)");
    h1_d->Draw("colz");
    tex->Draw();

    c1->cd(3);
    // gPad->SetLogz();  // 设置 Z 轴为对数刻度
    gStyle->SetOptStat(0);
    h1_e->SetTitle("Electron Energy Response Matrix;log_{10}Energy Incident(GeV);log_{10}Energy Deposit(GeV)");
    h1_e->Draw("colz");
    tex->Draw();

    c1->cd(4);
    // gPad->SetLogz();  // 设置 Z 轴为对数刻度
    gStyle->SetOptStat(0);
    h1_h->SetTitle("Helium4 Energy Response Matrix;log_{10}Energy Incident(GeV);log_{10}Energy Deposit(GeV)");
    h1_h->Draw("colz");
    tex->Draw();

    c1->SaveAs("/Users/xiongzheng/software/B4/B4c/Script/EnergyMatrix.pdf");

}