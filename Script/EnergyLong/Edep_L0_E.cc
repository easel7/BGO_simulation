void Edep_L0_E()
{
    auto proton_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Proton_10GeV.root");
    auto proton_tree = (TTree*)proton_file->Get("B4");

    proton_tree->Draw("L0_E:Total_E","First_Had_Layer>=1");
}