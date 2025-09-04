# AssetVerifier – Unreal Engine Asset Validation Plugin 

**AssetVerifier** es un plugin para Unreal Engine 5.6+ que valida y corrige automáticamente los assets del Content Browser.
Su objetivo es mantener estándares de calidad y consistencia en proyectos grandes, inspirado en frameworks de validación usados en estudios AAA.

## Funcionalidades

**Validadores** configurables (nombres, LODs, compresión, etc.)
**Fixers** automáticos para problemas comunes
**Reportes** (CSV, logs) con errores y advertencias
**Scopes** flexibles: todos los assets, por carpeta o selección actual
**Interfaz** en el Editor para ejecutar validadores y personalizar reglas

## Instalación

1. Descarga o clona este repositorio en la carpeta Plugins/ de tu proyecto Unreal:

    ```
    git clone https://github.com/tuusuario/AssetVerifier.git Plugins/AssetVerifier
    ```

2. Abre el proyecto en Unreal Engine 5.6+.
3. Activa el plugin desde Edit → Plugins → Other → AssetVerifier.
4. Reinicia el editor.

## Uso
1. Abre el menú Asset Verification en la barra de herramientas del Editor.
2. Selecciona el scope (All, Folder, Selected).
3. Ejecuta validadores o fixers desde la ventana.
4. Exporta el reporte a CSV o revisa el Output Log.

Ejemplo de flujo:
```
Run Validator → Run Fixer → Auto-Revalidate → Generate Report
```

## Estructura del Proyecto
```
AssetVerifier/
│── Source/
│   ├── AssetVerifier/               # Módulo principal
│   ├── Public/                      # Headers públicos
│   └── Private/                     # Implementación interna
│
│── Resources/                       # Íconos/UI
│── Config/                          # Configuración del plugin
│── AssetVerifier.uplugin            # Descriptor del plugin
```

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

## Contribución
Este proyecto tiene la meta de servir como pieza de portafolio para poder demonstrar mis habilidades como programador

## Autor
Brandon Retana

UCI – Game Design & Interactive Media + Data Science

Tools & Systems Programmer

[LinkedIn](https://www.linkedin.com/in/brandon-retana-3a7003295/)

Licencia: MIT – libre uso y modificación.
