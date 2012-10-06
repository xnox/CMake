/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef cmExportBuildFileGenerator_h
#define cmExportBuildFileGenerator_h

#include "cmExportFileGenerator.h"
#include "cmListFileCache.h"

/** \class cmExportBuildFileGenerator
 * \brief Generate a file exporting targets from a build tree.
 *
 * cmExportBuildFileGenerator generates a file exporting targets from
 * a build tree.  A single file exports information for all
 * configurations built.
 *
 * This is used to implement the EXPORT() command.
 */
class cmExportBuildFileGenerator: public cmExportFileGenerator
{
public:
  cmExportBuildFileGenerator();

  /** Set the list of targets to export.  */
  void SetTargets(std::vector<std::string> const& targets)
    { this->Targets = targets; }
  std::vector<std::string> const& GetTargets() const
    { return this->Targets; }
  void AppendTargets(std::vector<std::string> const& targets)
    { this->Targets.insert(this->Targets.end(),
      targets.begin(), targets.end()); }

  /** Set whether to append generated code to the output file.  */
  void SetAppendMode(bool append) { this->AppendMode = append; }

  void SetMakefile(cmMakefile *mf) {
    this->Makefile = mf;
    this->Makefile->GetBacktrace(this->Backtrace);
  }

protected:
  // Implement virtual methods from the superclass.
  virtual bool GenerateMainFile(std::ostream& os);
  virtual void GenerateImportTargetsConfig(std::ostream& os,
                                           const char* config,
                                           std::string const& suffix,
                            std::vector<std::string> &missingTargets);
  virtual void HandleMissingTarget(std::string& link_libs,
                                   std::vector<std::string>& missingTargets,
                                   cmMakefile* mf,
                                   cmTarget* depender,
                                   cmTarget* dependee);

  void ComplainAboutMissingTarget(cmTarget* depender,
                                  cmTarget* dependee);

  /** Fill in properties indicating built file locations.  */
  void SetImportLocationProperty(const char* config,
                                 std::string const& suffix,
                                 cmTarget* target,
                                 ImportPropertyMap& properties);

  std::string InstallNameDir(cmTarget* target, const std::string& config);

  std::vector<std::string> Targets;
  std::vector<cmTarget*> Exports;
  cmMakefile* Makefile;
  cmListFileBacktrace Backtrace;
};

#endif
