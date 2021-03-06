#include <string>
#include <iostream>
using namespace std;

#include "DenseMatrix.h"
#include "Mesh.h"
using namespace DDG;

// Command line parsing code courtesy Rohan Sawhney!

void printUsage(const std::string& programName)
{
   std::cout << "usage: "
             << programName << " "
             << "OBJ_INPUT_PATH "
             << "OBJ_OUTPUT_PATH "
             << "[--degree=n] "
             << "[--alignToCurvature] "
             << "[--alignToBoundary] "
             << "[--s=S] "
             << "[--t=T]"
             << std::endl;
}

bool doesArgExist(const std::string& arg, const std::string& searchStr)
{
   return arg.find(searchStr) != std::string::npos;
}

bool parseArg(const std::string& arg, const std::string& searchStr, std::string& value)
{
   if (doesArgExist(arg, searchStr)) {
      value = arg.substr(arg.find_first_of(searchStr[searchStr.size()-1]) + 1);
      return true;
   }

   return false;
}

void parseArgs(int argc, char *argv[], std::string& inputPath, std::string& outputPath,
      int& degree, bool& alignToCurvature, bool& alignToBoundary, double& s, double& t)
{
   if (argc < 3) {
      // input and/or output path not specified
      printUsage(argv[0]);
      exit(EXIT_FAILURE);

   } else {
      // parse arguments
      inputPath = argv[1];
      outputPath = argv[2];
      std::string degreeStr;
      std::string sStr, tStr;

      for (int i = 3; i < argc; i++) {
         if (parseArg(argv[i], "--degree=", degreeStr)) degree = std::stoi(degreeStr);
         if (doesArgExist(argv[i], "--alignToCurvature")) alignToCurvature = true;
         if (doesArgExist(argv[i], "--alignToBoundary")) alignToBoundary = true;
         if (parseArg(argv[i], "--s=", sStr)) s = std::atof(sStr.c_str());
         if (parseArg(argv[i], "--t=", tStr)) t = std::atof(tStr.c_str());
      }
   }

   // aligning to boundary takes precedence over aligning to curvature
   if (alignToBoundary) {
      alignToCurvature = false;
   }
}

int main( int argc, char** argv )
{
   // parse command line options
   std::string inputPath = "";
   std::string outputPath = "";
   int degree = 1;
   bool alignToCurvature = false;
   bool alignToBoundary = false;
   double s = 0.;
   double t = 0.;
   parseArgs( argc, argv, inputPath, outputPath, degree, alignToCurvature, alignToBoundary, s, t );

   Mesh mesh;

   cout << "Reading mesh from " << inputPath << "..." << endl;
   mesh.read( inputPath );

   cout << "Computing field..." << endl;
   mesh.InitKVecDirData();
   mesh.clearSingularities();
   if( alignToCurvature )
   {
      mesh.SmoothestCurvatureAlignment( degree, s, t, true );
   }
   else if( alignToBoundary )
   {
      mesh.ComputeSmoothestFixedBoundary( degree, s, true );
   }
   else
   {
      mesh.ComputeSmoothest( degree, s, true );
   }

   cout << "Writing solution to " << outputPath << "..." << endl;
   mesh.write( outputPath, degree );

   return 0;
}

