void Edep_Ratio()
{
    auto proton_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Electron_100GeV.root");
    auto proton_tree = (TTree*)proton_file->Get("B4");

    TCut UBT = "L0_E+L1_E>8";

    proton_tree->Draw("Total_E/Energy>>h0","","");
}