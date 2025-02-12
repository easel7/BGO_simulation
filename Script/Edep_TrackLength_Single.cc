void Edep_TrackLength_Single()
{
    auto proton_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Deuteron_100GeV.root");
    auto proton_tree = (TTree*)proton_file->Get("B4");
    auto c1 = new TCanvas("c1","c1",2000,1200);

    auto L0  = new TH2D("L0","L0",50,0,25,50,0,25);
    auto L1  = new TH2D("L1","L1",50,0,25,50,0,25);
    auto L2  = new TH2D("L2","L2",50,0,25,50,0,25);
    auto L3  = new TH2D("L3","L3",50,0,25,50,0,25);
    auto L4  = new TH2D("L4","L4",50,0,25,50,0,25);
    auto L5  = new TH2D("L5","L5",50,0,25,50,0,25);
    auto L6  = new TH2D("L6","L6",50,0,25,50,0,25);
    auto L7  = new TH2D("L7","L7",50,0,25,50,0,25);
    auto L8  = new TH2D("L8","L8",50,0,25,50,0,25);
    auto L9  = new TH2D("L9","L9",50,0,25,50,0,25);
    auto L10 = new TH2D("L10","L10",50,0,25,50,0,25);
    auto L11 = new TH2D("L11","L11",50,0,25,50,0,25);
    auto L12 = new TH2D("L12","L12",50,0,25,50,0,25);
    auto L13 = new TH2D("L13","L13",50,0,25,50,0,25);
    auto L14 = new TH2D("L14","L14",50,0,100,50,0,100);




    TCut UBT = "";

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
    proton_tree->Draw("Total_E:Total_L >>L14",UBT,"colz");


    c1->Clear();
    gStyle->SetOptStat(0);
    c1->Divide(5,3);
    
    c1->cd(1); L0->SetTitle( "Edep vs TrackLength in L0 ;TrackLength(m);Energy(GeV)");L0->Draw("colz");
    c1->cd(2); L1->SetTitle( "Edep vs TrackLength in L1 ;TrackLength(m);Energy(GeV)");L1->Draw("colz");
    c1->cd(3); L2->SetTitle( "Edep vs TrackLength in L2 ;TrackLength(m);Energy(GeV)");L2->Draw("colz");
    c1->cd(4); L3->SetTitle( "Edep vs TrackLength in L3 ;TrackLength(m);Energy(GeV)");L3->Draw("colz");
    c1->cd(5); L4->SetTitle( "Edep vs TrackLength in L4 ;TrackLength(m);Energy(GeV)");L4->Draw("colz");
    c1->cd(6); L5->SetTitle( "Edep vs TrackLength in L5 ;TrackLength(m);Energy(GeV)");L5->Draw("colz");
    c1->cd(7); L6->SetTitle( "Edep vs TrackLength in L6 ;TrackLength(m);Energy(GeV)");L6->Draw("colz");
    c1->cd(8); L7->SetTitle( "Edep vs TrackLength in L7 ;TrackLength(m);Energy(GeV)");L7->Draw("colz");
    c1->cd(9); L8->SetTitle( "Edep vs TrackLength in L8 ;TrackLength(m);Energy(GeV)");L8->Draw("colz");
    c1->cd(10);L9->SetTitle( "Edep vs TrackLength in L9 ;TrackLength(m);Energy(GeV)");L9->Draw("colz");
    c1->cd(11);L10->SetTitle("Edep vs TrackLength in L10;TrackLength(m);Energy(GeV)");L10->Draw("colz");
    c1->cd(12);L11->SetTitle("Edep vs TrackLength in L11;TrackLength(m);Energy(GeV)");L11->Draw("colz");
    c1->cd(13);L12->SetTitle("Edep vs TrackLength in L12;TrackLength(m);Energy(GeV)");L12->Draw("colz");
    c1->cd(14);L13->SetTitle("Edep vs TrackLength in L13;TrackLength(m);Energy(GeV)");L13->Draw("colz");
    c1->cd(15);L14->SetTitle("Total Edep vs TrackLength ;TrackLength(m);Energy(GeV)");L14->Draw("colz");


}