# AssetVerifier – Unreal Engine Asset Validation Plugin 

Disclaimer: This project is under the name of "PlugInProject" as it is under development, once shipped it will keep its name as "AssetVerifier."

This document is also available in [Español](README.es.md).

**AssetVerifier** is a plugin for **Unreal Engine 5.6+** that automatically validates and fixes assets in the Content Browser.  
Its goal is to enforce quality standards and consistency in large projects, inspired by AAA studio validation frameworks.  

---

## Features
- **Configurable Validators** (naming conventions, LODs, compression, etc.)  
- **Automatic Fixers** for common issues  
- **Reports** (CSV, JSON, logs) with errors and warnings  
- **Flexible Scopes**: all assets, by folder, or selected only  
- **Editor UI** to run validators and customize rules  

---

## Installation
1. Clone or download this repository into your Unreal project’s `Plugins/` folder:

    ```
    git clone https://github.com/youruser/AssetVerifier.git Plugins/AssetVerifier
3. Open the project in Unreal Engine 5.6+.
4. Enable the plugin in Edit → Plugins → Other → AssetVerifier.
5. Restart the editor.

---

## Usage
1. Open the Asset Verification menu in the Editor toolbar.
2. Select the scope (All, Folder, Selected).
3. Run validators or fixers from the window.
4. Export the report to CSV or check the Output Log.

Flow example:

    Run Validator → Run Fixer → Auto-Revalidate → Generate Report

## Project Structure

    AssetVerifier/
    │── Config/                          # Project configuration
    │── Source/                          # Main module
    │── Plugin/
        │── AssetVerifier/
            │── Resources/
            │── Source/
                │──AssetVerifier/
                    │── Private/
                        │── Fixers/
                            │── AssetLODFixer.cpp
                            │── AssetNamingFixer.cpp
                            │── FixerManager.cpp
                        │── Reporting/
                            │── AssetReportGenerator.cpp
                            │── AssetReportGenerator.h
                        │── UI/
                            │── AssetVerifierSettingsWindow.cpp
                            │── IssueRowWidget.cpp
                            │── IssuesDisplayView.cpp
                            │── ValidationReportWindow.cpp
                        │── Utils/
                            │── VerifierUtils.cpp
                            │── Verifierutils.h
                        │── Validators/
                            │── AssetFileSizeValidator.cpp
                            │── AssetLODValidator.cpp
                            │──
                    │── Plublic/
            │── AssetVerifier.uplugin    # Plug-in descriptor
    │── Saved/                           # Report Files; CSV & JSON
    │── AssetVerifier.uplugin            # Project descriptor


## Development

Language: C++ (UE5.6)
Editor UI: Slate / ToolMenus
Asset Management: AssetRegistry / UPackage APIs

## Roadmap
Basic validators (naming, LODs)
CSV report generation
Persistent settings UI for rules
Additional fixers (textures, materials)
Multi-user support (Perforce/Source Control)
 
Contributing
This is a solo project aim to demonstrate my skills as a programmer. For previous reason this project is not open for contributions.

## Author
Brandon Eduardo Retana García

UCI – Game Design & Interactive Media + Data Science

Tools & Systems Programmer

[LinkedIn](https://www.linkedin.com/in/brandon-retana-3a7003295/)

License: MIT – free to use and modify.

