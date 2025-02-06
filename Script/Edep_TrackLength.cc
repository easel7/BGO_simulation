void Edep_TrackLength()
{
    auto proton_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Proton_100GeV.root");
    auto proton_tree = (TTree*)proton_file->Get("B4");
    auto c1 = new TCanvas("c1","c1",1200,1200);

    auto L0 = new TH2D("L0","L0",60,0,30,60,0,30);
    auto L1 = new TH2D("L1","L1",60,0,30,60,0,30);
    auto L2 = new TH2D("L2","L2",60,0,30,60,0,30);
    auto L3 = new TH2D("L3","L3",60,0,30,60,0,30);

    TCut UBT = "L0_E+L1_E>8";

    proton_tree->Draw("L0_E:L0_L  >>L0",UBT,"colz");
    proton_tree->Draw("L4_E:L4_L  >>L1",UBT,"colz");
    proton_tree->Draw("L8_E:L8_L  >>L2",UBT,"colz");
    proton_tree->Draw("L12_E:L12_L>>L3",UBT,"colz");

    c1->Clear();
    gStyle->SetOptStat(0);
    c1->Divide(2,2);
    
    c1->cd(1);
    L0->SetTitle("Edep vs TrackLength in L0;TrackLength(mm);Energy(MeV)");
    L0->Draw("colz");

    c1->cd(2);
    L1->SetTitle("Edep vs TrackLength in L4;TrackLength(mm);Energy(MeV)");
    L1->Draw("colz");

    c1->cd(3);
    L2->SetTitle("Edep vs TrackLength in L8;TrackLength(mm);Energy(MeV)");
    L2->Draw("colz");

    c1->cd(4);
    L3->SetTitle("Edep vs TrackLength in L12;TrackLength(mm);Energy(MeV)");
    L3->Draw("colz");

}