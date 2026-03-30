# ⌨️ Keymap Personalizado Lily58 - Fernando

Configuración profesional de QMK para el teclado split Lily58, optimizada para soporte del idioma español, programación (Python/Android) y con una "Mascota de Teclado" en la pantalla OLED.

## 🚀 Características Principales

- **🇪🇸 Soporte Completo para Español**: Implementación de *Tap Dance* para un acceso fácil a acentos (á, é, í, ó, ú) y la ñ sin cambiar la distribución del sistema operativo.
- **🐕 Mascota OLED (Luna)**: Un perro animado en tu pantalla OLED que reacciona a tu velocidad de escritura y a teclas específicas (Ctrl para acechar, Espacio para saltar).
- **🎨 Retroiluminación RGB**: Iluminación dinámica con múltiples efectos (*Breathing*, *Rainbow*, *Knight*).
- **🖥️ Logos Multi-OS**: Logos de alta resolución para Linux, Python y Android en las pantallas OLED (maestro/esclavo).
- **⚡ Macros Pro**: 
  - `ALT_BSPC`: Combo inteligente de Backspace/Delete usando Alt.
  - `ALT_HOLD`: Optimización para alternar ventanas con Alt-Tab.
  - Macros de identidad secreta (Correos/Contraseñas vía `secrets.h`).

## 🗺️ Mapa de Capas (Layers)

### 0. BASE (QWERTY)
La capa principal con *Tap Dances* integrados para vocales acentuadas y caracteres especiales.
- **Tap Dance**: Presiona `e` para `e`, doble toque para `é`. (Lo mismo para a, i, o, u, n).
- **Teclas Pulgares**: Teclas de doble función `Espacio/Lower` y `Espacio/Raise`.

### 1. LOWER (Símbolos y Teclas F)
- **Símbolos Matemáticos**: `$ [ ] + | - # ( ) = &`
- **Teclas de Función**: F1 a F12.
- **Controles Multimedia**: Subir/Bajar Volumen, Play/Pause, Siguiente/Anterior.

### 2. RAISE (Navegación y Edición)
- **Flechas**: Navegación en el lado derecho.
- **Edición**: Atajos para Cortar, Copiar y Pegar.
- **Paginación**: Home, End, PgUp, PgDn.

### 3. ADJUST (Sistema y RGB)
- **Controles RGB**: Ajustes de encendido, tono (Hue), saturación y brillo.
- **Firmware**: Acceso a Reinicio (`QK_RBT`) y *Bootloader* (`QK_BOOT`).
- **Identidad**: Acceso a tus macros de Email1, Email2, Pass1, Pass2.

### 4. NUMBERS (Teclado Numérico)
- Un teclado numérico completo en el lado derecho para una entrada de datos rápida.

## 🛠️ Instrucciones de Flasheo

Para compilar y flashear este keymap en tu Lily58:

1.  Asegúrate de tener configurado el entorno QMK.
2.  Navega a la raíz de tu carpeta `qmk_firmware`.
3.  Ejecuta el siguiente comando:
    ```bash
    qmk flash -kb lily58 -km fernando
    ```

## 🔒 Nota de Seguridad: `secrets.h`

Este keymap utiliza un archivo `secrets.h` para almacenar información sensible como correos o contraseñas comunes.
- **NO** subas tu archivo `secrets.h` a un repositorio público.
- Se incluye un archivo de ejemplo `secrets-default.h`. Cópialo como `secrets.h` y rellénalo con tus datos.
- El archivo `.gitignore` en este directorio ya está configurado para ignorar `secrets.h`.

---
*Creado con ❤️ por [Fernando (NandoDev1997)](https://github.com/NandoDev1997)*
