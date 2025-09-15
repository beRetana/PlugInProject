# AssetVerifier – Unreal Engine Asset Validation Plugin 

> [!NOTE]
> Disclaimer: This project is under the name of "PlugInProject" as it is under development, once shipped it will keep its name as "AssetVerifier."

> [!TIP]
> This document is also available in [Español](README.es.md).

**AssetVerifier** is a plugin for **Unreal Engine 5.6+** that automatically validates and fixes assets in the Content Browser.  
Its goal is to enforce quality standards and consistency in large projects, inspired by AAA studio validation frameworks.  

---

## Demo Videos

> [!Note]
> This video shows how the plug-in can be used to fix naming conventions!

[![Video Demo](https://img.youtube.com/vi/0AxqsjTn1OA/0.jpg)](https://www.youtube.com/watch?v=0AxqsjTn1OA)

> [!Note]
> This video shows how the plug-in exports reports into various formats!

[![Video Demo](https://img.youtube.com/vi/HZARlAZU9Og/0.jpg)](https://www.youtube.com/watch?v=HZARlAZU9Og)

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
    git clone https://github.com/beRetana/PlugInProject.git
    ```
2. Open the project in Unreal Engine 5.6+.
3. Enable the plugin in Edit → Plugins → Other → AssetVerifier.
4. Restart the editor.

---

## Usage
1. Open the Asset Verification menu in the Editor toolbar.
2. Select the scope (All, Folder, Selected).
3. Run validators or fixers from the window.
4. Export the report to CSV or check the Output Log.

Flow example:
```
    Run Validator → Generate Report → Run Fixer 
```

---

## Project Structure

- `Plugin/`
  - `AssetVerifier/`
    - `Resources/` (Icons, resources, plugin assets)
    - `Source/`
      - `AssetVerifier/`
        - `Private/` (Implementation files)
          - `Fixers/` (Automatic asset fixers)
          - `Reporting/` (Report generation logic)
          - `UI/` (Slate UI windows & widgets)
          - `Utils/` (Helper utilities)
          - `Validators/` (Asset validation rules)
          - *(other core .cpp files: managers, settings, commands, scope builder)*
        - `Public/` (Exposed plugin APIs)
          - `Fixers/` (Fixer interfaces & headers)
          - `UI/` (Public widget & window headers)
          - `Validators/` (Validator interfaces & headers)
          - *(core public headers: settings, data, commands, etc.)*
        - `AssetVerifier.Build.cs` (Build script)
    - `AssetVerifier.uplugin` (Plugin descriptor)
- `Saved/` (Generated reports: CSV, JSON)
- `AssetVerifier.uplugin` (Project descriptor)

---

## Development

- Language: C++ (UE5.6)
- Editor UI: Slate / ToolMenus
- Asset Management: AssetRegistry / UPackage APIs

## Roadmap
- Basic validators (naming, LODs)
- CSV report generation
- Persistent settings UI for rules
- Additional fixers (textures, materials)
- Multi-user support (Perforce/Source Control)

## Author
Brandon Eduardo Retana García

UCI – Game Design & Interactive Media + Data Science

Tools & Systems Programmer [LinkedIn](https://www.linkedin.com/in/brandon-retana-3a7003295/)

> [!Warning]
> This is a solo project aim to demonstrate my skills as a programmer. For previous reasons this project is not open for contributions.

