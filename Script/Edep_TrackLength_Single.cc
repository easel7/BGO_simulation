void Edep_TrackLength_Single()
{
    auto proton_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Proton_1000GeV.root");
    auto proton_tree = (TTree*)proton_file->Get("B4");
    auto c1 = new TCanvas("c1","c1",2000,1200);

    auto L0  = new TH2D("L0","L0",60,0,30,60,0,30);
    auto L1  = new TH2D("L1","L1",60,0,30,60,0,30);
    auto L2  = new TH2D("L2","L2",60,0,30,60,0,30);
    auto L3  = new TH2D("L3","L3",60,0,30,60,0,30);
    auto L4  = new TH2D("L4","L4",60,0,30,60,0,30);
    auto L5  = new TH2D("L5","L5",60,0,30,60,0,30);
    auto L6  = new TH2D("L6","L6",60,0,30,60,0,30);
    auto L7  = new TH2D("L7","L7",60,0,30,60,0,30);
    auto L8  = new TH2D("L8","L8",60,0,30,60,0,30);
    auto L9  = new TH2D("L9","L9",60,0,30,60,0,30);
    auto L10 = new TH2D("L10","L10",60,0,30,60,0,30);
    auto L11 = new TH2D("L11","L11",60,0,30,60,0,30);
    auto L12 = new TH2D("L12","L12",60,0,30,60,0,30);
    auto L13 = new TH2D("L13","L13",60,0,30,60,0,30);



    TCut UBT = "First_Type==0";

    proton_tree->Draw("L0_E :L0_L  >>L0",UBT,"colz");
    proton_tree->Draw("L1_E :L1_L  >>L1",UBT,"colz");
    proton_tree->Draw("L2_E :L2_L  >>L2",UBT,"colz");
    proton_tree->Draw("L3_E :L3_L  >>L3",UBT,"colz");
    proton_tree->Draw("L4_E :L4_L  >>L4",UBT,"colz");
    proton_tree->Draw("L5_E :L5_L  >>L5",UBT,"colz");
    proton_tree->Draw("L6_E :L6_L  >>L6",UBT,"colz");
    proton_tree->Draw("L7_E :L7_L  >>L7",UBT,"colz");
    proton_tree->Draw("L8_E :L8_L  >>L8",UBT,"colz");
    proton_tree->Draw("L9_E :L9_L  >>L9",UBT,"colz");
    proton_tree->Draw("L10_E:L10_L >>L10",UBT,"colz");
    proton_tree->Draw("L11_E:L11_L >>L11",UBT,"colz");
    proton_tree->Draw("L12_E:L12_L >>L12",UBT,"colz");
    proton_tree->Draw("L13_E:L13_L >>L13",UBT,"colz");

    c1->Clear();
    gStyle->SetOptStat(0);
    c1->Divide(5,3);
    
    c1->cd(1); L0->SetTitle( "Edep vs TrackLength in L0 ;TrackLength(mm);Energy(MeV)");L0->Draw("colz");
    c1->cd(2); L1->SetTitle( "Edep vs TrackLength in L1 ;TrackLength(mm);Energy(MeV)");L1->Draw("colz");
    c1->cd(3); L2->SetTitle( "Edep vs TrackLength in L2 ;TrackLength(mm);Energy(MeV)");L2->Draw("colz");
    c1->cd(4); L3->SetTitle( "Edep vs TrackLength in L3 ;TrackLength(mm);Energy(MeV)");L3->Draw("colz");
    c1->cd(5); L4->SetTitle( "Edep vs TrackLength in L4 ;TrackLength(mm);Energy(MeV)");L4->Draw("colz");
    c1->cd(6); L5->SetTitle( "Edep vs TrackLength in L5 ;TrackLength(mm);Energy(MeV)");L5->Draw("colz");
    c1->cd(7); L6->SetTitle( "Edep vs TrackLength in L6 ;TrackLength(mm);Energy(MeV)");L6->Draw("colz");
    c1->cd(8); L7->SetTitle( "Edep vs TrackLength in L7 ;TrackLength(mm);Energy(MeV)");L7->Draw("colz");
    c1->cd(9); L8->SetTitle( "Edep vs TrackLength in L8 ;TrackLength(mm);Energy(MeV)");L8->Draw("colz");
    c1->cd(10);L9->SetTitle( "Edep vs TrackLength in L9 ;TrackLength(mm);Energy(MeV)");L9->Draw("colz");
    c1->cd(11);L10->SetTitle("Edep vs TrackLength in L10;TrackLength(mm);Energy(MeV)");L10->Draw("colz");
    c1->cd(12);L11->SetTitle("Edep vs TrackLength in L11;TrackLength(mm);Energy(MeV)");L11->Draw("colz");
    c1->cd(13);L12->SetTitle("Edep vs TrackLength in L12;TrackLength(mm);Energy(MeV)");L12->Draw("colz");
    c1->cd(14);L13->SetTitle("Edep vs TrackLength in L13;TrackLength(mm);Energy(MeV)");L13->Draw("colz");


}