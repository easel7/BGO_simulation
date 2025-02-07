double smartCeil(double value);

void Edep_Layer_Single()
{


    auto proton_file = TFile::Open("/Users/xiongzheng/software/B4/B4c/Root/Deuteron_100GeV.root");
    auto proton_tree = (TTree*)proton_file->Get("B4");
    auto c1 = new TCanvas("c1","c1",900,600);

    double max_TotalE = proton_tree->GetMaximum("Total_E");
    double max_Energy = proton_tree->GetMaximum("Energy");


    cout << "Max value of Total_E: " << max_TotalE << "MeV" << endl;
    cout << "Total_E / max_Energy: " << max_TotalE/max_Energy << endl;
    cout << "ceil Max value of Total_E: " << smartCeil(max_TotalE/max_Energy)  << endl;
    auto *h0 = new TH1D("h0","h0",100,0,smartCeil(max_TotalE/max_Energy)); // Energy Deposit Ratio

    proton_tree->Draw("Total_E/Energy>>h0","","");
    h0->SetTitle("Energy Deposit Ratio;Energy Deposit / Incident Kinetic Energy;No. Events");
    h0->Fit("gaus");

    std::cout << smartCeil(0.17) << std::endl;   // Expected: 0.20
    std::cout << smartCeil(0.21) << std::endl;   // Expected: 0.25
    std::cout << smartCeil(0.017) << std::endl;  // Expected: 0.02
    std::cout << smartCeil(1.78) << std::endl;   // Expected: 2.00
    std::cout << smartCeil(2.49) << std::endl;   // Expected: 2.50
    std::cout << smartCeil(2.49e-5) << std::endl;   // Expected: 2.50

}

double smartCeil(double value) {
    if (value == 0) return 0.0; // Edge case for zero
    // Determine the order of magnitude
    double order = pow(10, floor(log10(value)));
    // Scale the value to a range where rounding works
    double scaled_value = value / order;
    // Round up to the nearest multiple of 0.05
    double rounded_scaled = ceil(scaled_value * 20) / 20; // 0.05 = 1/20
    // Restore the original scale
    return rounded_scaled * order;
}