#ifndef Analysis_Tools_macro_config_h_
#define Analysis_Tools_macro_config_h_

#include "boost/program_options.hpp"
#include "boost/algorithm/string.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

int macro_config(int argc, char * argv[]);

std::string cfg_;

int nevtmax_;
int nlumis_;
bool isMC_;
bool signalregion_;
std::string inputlist_;
std::string outputRoot_;
std::string json_;

//
bool matchonoff_;
float matchonoffdrmax_;
bool matchonoffref_;
bool psweight_;
bool trigemul_;


// triggerobjects emulation
int ntomin_[10];
std::vector<float> toptmin_[10];
std::vector<float> toetamax_[10];


// jets

int njetsmin_;
int nbjetsmin_;
std::vector<float> jetsptmin_;
std::vector<float> jetsptmax_;
std::vector<float> jetsetamax_;
std::vector<float> jetsbtagmin_;
std::string jetsid_;

int l1tjetsnmin_;
std::vector<float> l1tjetsptmin_;
std::vector<float> l1tjetsetamax_;


// muons

int nmuonsmin_;
std::vector<float> muonsptmin_;
std::vector<float> muonsptmax_;
std::vector<float> muonsetamax_;
std::string muonsid_;

int l1tmuonsnmin_;
std::vector<float> l1tmuonsptmin_;
std::vector<float> l1tmuonsetamax_;



// additional cuts of unidentified objects or for extra selections
int nmin_;
std::vector<float> ptmin_;
std::vector<float> etamax_;


float drmin_;
float drmax_;
float detamax_;
float dphimin_;

std::string btagalgo_;
float btagwploose_;
float btagwpmedium_;
float btagwptight_;
float btagwp_;
float nonbtagwp_;


std::string hltPath_;
std::string l1Seed_;
std::string hltPathRef_;
std::vector<std::string> triggerObjects_;
std::vector<std::string> hltPaths_;
std::string hltPathsLogic_;
std::vector<std::string> hltPaths2_;
std::string hltPathsLogic2_;
std::vector<std::string> triggerObjectsJets_;
std::vector<std::string> triggerObjectsMuons_;

// ntuples collections
std::string treePath_;
std::string jetsCol_; 
std::string muonsCol_; 
std::string l1tjetsCol_; 
std::string l1tmuonsCol_; 
std::string triggerCol_;
std::string triggerObjDir_;

int macro_config(int argc, char * argv[])
{
   try
   {
      namespace po = boost::program_options;
      po::options_description desc("Options");
      desc.add_options()
         ("help,h","Show help messages")
         ("config,c",po::value<std::string>(&cfg_),"Configuration file name");
      
      po::options_description config("Configuration");
      config.add_options()
         ("ntuplesList",po::value <std::string> (&inputlist_)->default_value("rootFileList.txt"),"File with list of ntuples")
         ("nEventsMax",po::value <int> (&nevtmax_)->default_value(-1), "Maximum number of events")
         ("nLumiSections",po::value <int> (&nlumis_)->default_value(-1), "Number of lumi sections processed")
         ("output",po::value <std::string> (&outputRoot_)->default_value("histograms.root"),"Output root file")
         ("json",po::value <std::string> (&json_)->default_value("no_json.txt"),"JSON file for data")
//      
         ("nJetsMin",po::value <int> (&njetsmin_)->default_value(0),"Minimum number of jets")
         ("nBJetsMin",po::value <int> (&nbjetsmin_)->default_value(0),"Minimum number of btgaged jets")
         ("jetsPtMin", po::value<std::vector<float> >(&jetsptmin_)->multitoken(),"Mimium pt of the jets")
         ("jetsPtMax", po::value<std::vector<float> >(&jetsptmax_)->multitoken(),"Maximum pt of the jets")
         ("jetsEtaMax", po::value<std::vector<float> >(&jetsetamax_)->multitoken(),"Maximum |eta| of the jets")
         ("jetsBtagMin", po::value<std::vector<float> >(&jetsbtagmin_)->multitoken(),"Minimum btag of the jets; if < 0 -> reverse btag")
         ("jetsId",po::value <std::string> (&jetsid_)->default_value("LOOSE"),"Jets id criteria for all jets")
         
         ("l1tJetsNMin",po::value <int> (&l1tjetsnmin_)->default_value(0),"Minimum number of L1T jets")
         ("l1tJetsPtMin", po::value<std::vector<float> >(&l1tjetsptmin_)->multitoken(),"Mimium pt of the L1T jets")
         ("l1tJetsEtaMax", po::value<std::vector<float> >(&l1tjetsetamax_)->multitoken(),"Maximum |eta| of the L1T jets")
         
//      
         ("nMuonsMin",po::value <int> (&nmuonsmin_)->default_value(0),"Minimum number of muons")
         ("muonsPtMin", po::value<std::vector<float> >(&muonsptmin_)->multitoken(),"Mimium pt of the muons")
         ("muonsPtMax", po::value<std::vector<float> >(&muonsptmax_)->multitoken(),"Maximum pt of the muons")
         ("muonsEtaMax", po::value<std::vector<float> >(&muonsetamax_)->multitoken(),"Maximum |eta| of the muons")
         ("muonsId",po::value <std::string> (&muonsid_)->default_value("LOOSE"),"muons id criteria for all muons")
         
         ("l1tMuonsNMin",po::value <int> (&l1tmuonsnmin_)->default_value(0),"Minimum number of L1T muons")
         ("l1tMuonsPtMin", po::value<std::vector<float> >(&l1tmuonsptmin_)->multitoken(),"Mimium pt of the L1T muons")
         ("l1tMuonsNEtaMax", po::value<std::vector<float> >(&l1tmuonsetamax_)->multitoken(),"Maximum |eta| of the L1T muons")
         
//
         ("nMin",po::value <int> (&nmin_)->default_value(0),"Minimum number objects")
         ("ptMin", po::value<std::vector<float> >(&ptmin_)->multitoken(),"Mimium pt of an object")
         ("etaMax", po::value<std::vector<float> >(&etamax_)->multitoken(),"Maximum |eta| of an object")
//
         ("dRMin",po::value <float> (&drmin_)->default_value(0.),"Minimum delta R between candidates")
         ("dRMax",po::value <float> (&drmax_)->default_value(0.),"Maximum delta R between candidates")
         ("dEtaMax",po::value <float> (&detamax_)->default_value(10.),"Maximum delta eta between candidates")
         ("dPhiMin",po::value <float> (&dphimin_)->default_value(0.),"Minimum delta phi between candidates")
//      
         ("isMC",po::value <bool> (&isMC_)->default_value(true),"Flag for MC dataset")
         ("signalRegion",po::value <bool> (&signalregion_)->default_value(true),"Flag for signal region")
         ("hltPath",po::value <std::string> (&hltPath_),"HLT path name")
         ("l1Seed",po::value <std::string> (&l1Seed_)->default_value(""),"L1 seed name")
         ("hltPathReference",po::value <std::string> (&hltPathRef_),"HLT path name for reference trigger for trigger efficiency")
         ("triggerObjects", po::value<std::vector<std::string> >(&triggerObjects_)->multitoken(),"Trigger objects")
         ("hltPathsList", po::value<std::vector<std::string> >(&hltPaths_)->multitoken(),"HLT paths list")
         ("hltPathsLogic",po::value <std::string> (&hltPathsLogic_)->default_value("OR"),"HLT paths logic (OR/AND)")
         ("hltPathsList2", po::value<std::vector<std::string> >(&hltPaths2_)->multitoken(),"HLT paths second list")
         ("hltPathsLogic2",po::value <std::string> (&hltPathsLogic2_)->default_value("OR"),"HLT paths logic (OR/AND) for second list")
         ("triggerObjectsJets", po::value<std::vector<std::string> >(&triggerObjectsJets_)->multitoken(),"Trigger objects for jets")
         ("triggerObjectsMuons", po::value<std::vector<std::string> >(&triggerObjectsMuons_)->multitoken(),"Trigger objects for muons")
//      
         ("btagAlgorithm",po::value <std::string> (&btagalgo_)->default_value("csvivf"),"BTag algorithm")
         ("btagWPLoose",po::value <float> (&btagwploose_)->default_value(0.46),"BTag working point LOOSE")
         ("btagWPMedium",po::value <float> (&btagwpmedium_)->default_value(0.84),"BTag working point MEDIUM")
         ("btagWPTight",po::value <float> (&btagwptight_)->default_value(0.92),"BTag working point TIGHT")
//         
         ("btagWP",po::value <float> (&btagwp_)->default_value(0.8484),"Btag working point")
         ("nonbtagWP",po::value <float> (&nonbtagwp_)->default_value(0.46),"non-Btag working point")
         
//
         ("matchOnlineOffline",po::value <bool> (&matchonoff_)->default_value(true),"Flag for doing matching online offline objects")
         ("matchOnlineOfflineDeltaRMax",po::value <float> (&matchonoffdrmax_)->default_value(0.4),"DeltaR max for matching online-offline")
         ("matchOnlineOfflineReference",po::value <bool> (&matchonoffref_)->default_value(true),"Flag for doing matching online offline objects when using a reference trigger")
         ("prescaleWeight",po::value <bool> (&psweight_)->default_value(false),"Flag for weighting histograms with prescale")
         ("triggerEmulation",po::value <bool> (&trigemul_)->default_value(false),"Flag for using trigger emulation")
         
         ("jetsCollection",po::value <std::string> (&jetsCol_)->default_value("slimmedJetsPuppi"),"Name of the jets collection")
         ("muonsCollection",po::value <std::string> (&muonsCol_)->default_value("slimmedMuons"),"Name of the muons collection")
         ("l1tJetsCollection",po::value <std::string> (&l1tjetsCol_)->default_value("l1tJets"),"Name of the L1T jets collection")
         ("l1tMuonsCollection",po::value <std::string> (&l1tmuonsCol_)->default_value("l1tMuons"),"Name of the L1T muons collection")

         ("triggerResultsCollection",po::value <std::string> (&triggerCol_)->default_value("TriggerResults"),"Name of the trigger results collection")
         ("triggerObjectsDirectory",po::value <std::string> (&triggerObjDir_)->default_value("slimmedPatTrigger"),"Name of the trigger objects directory")
         ("collectionsTreePath",po::value <std::string> (&treePath_)->default_value("Events"),"Name of the tree path for the event collections.");
         
         

         for ( int i = 0 ; i < 10 ; ++i )
         {
            config.add_options()
               (Form("triggerObject%dNMin",i),po::value <int> (&(ntomin_[i]))->default_value(0),Form("Minimum number of trigger objects #%d",i))
               (Form("triggerObject%dPtMin",i),po::value<std::vector<float> >(&(toptmin_[i]))->multitoken(),Form("Minimum pT of trigger objects #%d",i))
               (Form("triggerObject%dEtaMax",i),po::value<std::vector<float> >(&(toetamax_[i]))->multitoken(),Form("Minimum eta of trigger objects #%d",i));
         }
      
      po::variables_map vm; 
      try
      {
         po::store(po::parse_command_line(argc, argv, desc), vm); // can throw
         // --help option
         
         if ( vm.count("help") )
         {
            std::cout << "SimpleBjetsAnalysis macro" << std::endl
                      << desc << std::endl
                      << config << std::endl;
            return 1;
         }
         po::notify(vm);
         
         std::ifstream cfg_s(cfg_.c_str());
         po::store(po::parse_config_file(cfg_s, config), vm); // can throw
         if ( vm.count("config") )
         {

         }
         po::notify(vm);
         boost::algorithm::to_upper(jetsid_);
         if ( (int)jetsptmin_.size() != njetsmin_ )
         {
            std::cout << "Config Error *** Jet minimum pt were not defined or the definition does not match the minimum number of jets" <<std::endl;
            return -1;
         }
         if ( (int)jetsptmax_.size() != njetsmin_ && !jetsptmax_.empty() )
         {
            std::cout << "Config Error *** Jet maximum pt has been defined and does not match the minimum number of jets" <<std::endl;
            return -1;
         }
         if ( (int)jetsetamax_.size() != njetsmin_ )
         {
            std::cout << "Config Error *** Jet maximum |eta| were not defined or the definition does not match the minimum number of jets" <<std::endl;
            return -1;
         }
         if ( (int)jetsbtagmin_.size() != nbjetsmin_ && !jetsbtagmin_.empty() )
         {
            std::cout << "Config Error *** Jet minimum btag has been defined and does not match the minimum number of btagged jets" <<std::endl;
            return -1;
         }

         
         if ( (int)muonsptmin_.size() != nmuonsmin_ )
         {
            std::cout << "Config Error *** Muon minimum pt were not defined or the definition does not match the minimum number of muons" <<std::endl;
            return -1;
         }
         if ( (int)muonsptmax_.size() != nmuonsmin_ && !muonsptmax_.empty() )
         {
            std::cout << "Config Error *** Muon maximum pt has been defined and does not match the minimum number of muons" <<std::endl;
            return -1;
         }
         if ( (int)muonsetamax_.size() != nmuonsmin_ )
         {
            std::cout << "Config Error *** Muon maximum |eta| were not defined or the definition does not match the minimum number of muons" <<std::endl;
            return -1;
         }
         
         
      }
      catch(po::error& e)
      { 
         std::cerr << "ERROR: " << e.what() << std::endl << std::endl; 
         std::cerr << desc << std::endl; 
         return -1; 
      } 
      
   }
   catch(std::exception& e) 
   { 
      std::cerr << "ERROR: " << e.what() << std::endl << std::endl; 
      return -1; 
   } 
   
   return 0;
}

   
#endif
