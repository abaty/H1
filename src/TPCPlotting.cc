#include "TH2D.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TLegend.h"
#include "include/multTool.h"
#include <iostream>

void formatTPCAxes(TH2D * h, float offsetx = 1.5, float offsety = 1.5, float offsetz = 1.4, float axisLabelSize = 0.05){
    h->SetStats(0);
    
    h->SetTitleOffset(offsetx,"X");
    h->SetTitleSize(0.055,"X");
    h->GetXaxis()->CenterTitle();
    h->SetLabelSize(axisLabelSize,"X");
    h->SetLabelFont(42,"X");
    h->SetNdivisions(505,"X");
    h->GetXaxis()->SetTitle("#Delta#eta");
    
    h->SetTitleOffset(offsety,"Y");
    h->SetTitleSize(0.055,"Y");
    h->GetYaxis()->CenterTitle();
    h->SetLabelSize(axisLabelSize,"Y");
    h->SetLabelFont(42,"Y");
    h->SetNdivisions(505,"Y");
    h->GetYaxis()->SetTitle("#Delta#phi");
    
    h->SetTitleOffset(offsetz,"Z");
    h->SetTitleSize(0.055,"Z");
    h->GetZaxis()->CenterTitle();
    h->SetLabelSize(axisLabelSize,"Z");
    h->SetLabelFont(42,"Z");
    h->SetNdivisions(505,"Z");
    h->GetZaxis()->SetTitle("#frac{1}{N^{trig}} #frac{d^{2}N^{pair}}{d#Delta#etad#Delta#phi}");

    h->SetLineColor(kBlack);    
}

void setupCanvas(TVirtualPad *c1)
{
          c1->SetLeftMargin(0.2);
          c1->SetTheta(60.839);
          c1->SetPhi(38.0172);
}

void formatZaxis(TH2D * h){
    float maximum = -1;
    float minimum = 99999;
    float averageSum = 0;
    float averageCounter = 0;

    float dphi_peakMin = -1;
    float dphi_peakMax = 1;
    float deta_peakMin = -2;
    float deta_peakMax = 2;
    
    for(int i = 1; i<h->GetXaxis()->GetNbins()+1; i++){
        for(int j = 1; j<h->GetYaxis()->GetNbins()+1; j++){
            if( h->GetYaxis()->GetBinCenter(j) >= dphi_peakMin && h->GetYaxis()->GetBinCenter(j) <= dphi_peakMax && h->GetXaxis()->GetBinCenter(i) >= deta_peakMin && h->GetXaxis()->GetBinCenter(i) <= deta_peakMax) continue;
            if(h->GetBinContent(i,j)>=maximum) maximum = h->GetBinContent(i,j);
            if(h->GetBinContent(i,j)<=minimum) minimum = h->GetBinContent(i,j);
            averageSum += h->GetBinContent(i,j);
            averageCounter++;
        }
    }
    float mean = averageSum/averageCounter;
    std::cout << maximum << " " << minimum << " " << averageSum/averageCounter << std::endl;
    
    h->GetZaxis()->SetRangeUser(minimum-0.2*(mean-minimum),maximum);
}

void TPCPlotting(){

  TFile * input = TFile::Open("Dec16_TPC.root","read");
  MultTool mt = MultTool();
  
  TH2D * twoParticleCorrSig[mt.nMultBins];
  TH2D * twoParticleCorrBkg[mt.nMultBins];
  TH2D * twoParticleCorrRat[mt.nMultBins];
  TCanvas * c1;
  TLegend * l;
  for( int i = 0; i<mt.nMultBins; i++){
    twoParticleCorrSig[i] = (TH2D*)input->Get(Form("twoParticleCorrSig_%d_%d",mt.multBinLowerBoundary[i], mt.multBinUpperBoundary[i]));
    twoParticleCorrBkg[i] = (TH2D*)input->Get(Form("twoParticleCorrBkg_%d_%d",mt.multBinLowerBoundary[i], mt.multBinUpperBoundary[i]));
    twoParticleCorrRat[i] = (TH2D*)input->Get(Form("twoParticleCorrRat_%d_%d",mt.multBinLowerBoundary[i], mt.multBinUpperBoundary[i]));
  
    c1 = new TCanvas("c1","c1",600,600);

    setupCanvas(c1);
    formatTPCAxes(twoParticleCorrSig[i]);
    formatZaxis(twoParticleCorrSig[i]);

    twoParticleCorrSig[i]->Draw("surf1 fb");

    l = new TLegend(-0.1,0.71333,0.40,0.98);
    l->SetFillStyle(0);
    l->SetBorderSize(0);
    l->SetTextSize(0.038);
    l->AddEntry((TObject*)0,"H1 Data","");
    l->AddEntry((TObject*)0,"Q^{2} > 5 GeV^{2}","");
    l->AddEntry((TObject*)0,"p_{T}^{trk}>0.15 GeV","");
    l->AddEntry((TObject*)0,"-1.2 < #eta^{trk} < 1.6","");
    l->AddEntry((TObject*)0,Form("%d #leq N^{trk} < %d",mt.multBinLowerBoundary[i], mt.multBinUpperBoundary[i]),"");
    l->Draw("same");

    c1->SaveAs(Form("plots/twoParticleCorrSig_%d_%d.png",mt.multBinLowerBoundary[i], mt.multBinUpperBoundary[i]));
    c1->SaveAs(Form("plots/twoParticleCorrSig_%d_%d.pdf",mt.multBinLowerBoundary[i], mt.multBinUpperBoundary[i]));
    
    formatTPCAxes(twoParticleCorrBkg[i]);
    formatZaxis(twoParticleCorrBkg[i]);

    twoParticleCorrBkg[i]->Draw("surf1 fb");
    l->Draw("same");
    
    c1->SaveAs(Form("plots/twoParticleCorrBkg_%d_%d.png",mt.multBinLowerBoundary[i], mt.multBinUpperBoundary[i]));
    c1->SaveAs(Form("plots/twoParticleCorrBkg_%d_%d.pdf",mt.multBinLowerBoundary[i], mt.multBinUpperBoundary[i]));
    
    formatTPCAxes(twoParticleCorrRat[i]);
    formatZaxis(twoParticleCorrRat[i]);

    twoParticleCorrRat[i]->Draw("surf1 fb");
    l->Draw("same");
    
    c1->SaveAs(Form("plots/twoParticleCorrRat_%d_%d.png",mt.multBinLowerBoundary[i], mt.multBinUpperBoundary[i]));
    c1->SaveAs(Form("plots/twoParticleCorrRat_%d_%d.pdf",mt.multBinLowerBoundary[i], mt.multBinUpperBoundary[i]));

    delete c1;
  }
}

int main(){
  TPCPlotting(); 
}
