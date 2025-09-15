# AssetVerifier – Unreal Engine Asset Validation Plugin 

> [!NOTE]
> Disclaimer: Este proyecto esta bajo el nombre de "PlugInProject" porque es bajo desarrollo una vez este publicado se llamará "AssetVerifier."

> [!TIP]
> Este documento también esta en [English](README.md).

**AssetVerifier** es un plugin para **Unreal Engine 5.6+** que valida y corrige automáticamente los assets del Content Browser.
Su objetivo es mantener estándares de calidad y consistencia en proyectos grandes, inspirado en frameworks de validación usados en estudios AAA.

---

## Funcionalidades

**Validadores** configurables (nombres, LODs, compresión, etc.)
**Fixers** automáticos para problemas comunes
**Reportes** (CSV, logs) con errores y advertencias
**Scopes** flexibles: todos los assets, por carpeta o selección actual
**Interfaz** en el Editor para ejecutar validadores y personalizar reglas

---

## Instalación

1. Descarga o clona este repositorio en la carpeta `Plugins/` de tu proyecto Unreal:

```
git clone https://github.com/beRetana/PlugInProject.git
```

2. Abre el proyecto en Unreal Engine 5.6+.
3. Activa el plugin desde Edit → Plugins → Other → AssetVerifier.
4. Reinicia el editor.

---

## Uso
1. Abre el menú Asset Verification en la barra de herramientas del Editor.
2. Selecciona el scope (All, Folder, Selected).
3. Ejecuta validadores o fixers desde la ventana.
4. Exporta el reporte a CSV o revisa el Output Log.

Ejemplo de flujo:
```
Run Validator → Run Fixer → Auto-Revalidate → Generate Report
```

---

## Estructura del Proyecto

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

## Desarrollo
- Lenguaje: C++ (UE5.6)
- UI de Editor: Slate / ToolMenus
- Gestión de Assets: AssetRegistry / UPackage APIs

## Roadmap
- Validadores básicos (nombres, LODs)
- Generación de reporte en CSV
- Configuración persistente de reglas desde UI
- Fixers adicionales (texturas, materiales)
- Soporte multiusuario (Perforce/Source Control)

## Autor
Brandon Retana

UCI – Game Design & Interactive Media + Data Science

Tools & Gameplay Programmer [LinkedIn](https://www.linkedin.com/in/brandon-retana-3a7003295/)

> [!Warning]
> Este proyecto tiene el objetivo de ser usado para mi portafolio personal por lo cual las contribuciones no están permitidas.
