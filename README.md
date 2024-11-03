Discord bot to track fast-growing crypto-currencies


```bash
crypto_tui/                  # Proyecto principal
│
├── src/                     # Código fuente principal
│   ├── main.cpp             # Punto de entrada del programa, inicializa la TUI.
│   ├── api/                 # Módulo para las APIs de criptomonedas
│   │   ├── api_manager.cpp  # Manejador de las llamadas a las APIs.
│   │   └── api_manager.h    # Declaración de funciones de API para obtener precios y datos de criptos.
│   │
│   ├── ui/                  # Módulo de la interfaz de usuario (con FTXUI)
│   │   ├── tui.cpp          # Lógica de la interfaz TUI usando FTXUI.
│   │   └── tui.h            # Declaración de funciones y clases de la TUI.
│   │
│   ├── models/              # Modelos de datos para criptomonedas, notas y wallets
│   │   ├── crypto.cpp       # Clase de representación de una criptomoneda.
│   │   ├── crypto.h         # Declaración de los datos y métodos de criptos.
│   │   ├── note.cpp         # Clase de representación de una nota.
│   │   ├── note.h           # Declaración de métodos para notas, incluyendo edición en vim/nvim.
│   │   ├── wallet.cpp       # Clase para manejar datos de la wallet.
│   │   └── wallet.h         # Declaración de los métodos de la wallet.
│   │
│   ├── utils/               # Utilidades y funciones comunes
│   │   ├── config.cpp       # Manejo de configuración (por ejemplo, editor para notas).
│   │   └── config.h         # Declaración de funciones de configuración.
│
├── data/                    # Almacenamiento de datos locales
│   ├── notes/               # Carpeta para almacenar notas.
│   └── favorites.txt        # Lista de criptomonedas favoritas.
│
├── assets/                  # Recursos adicionales
│   └── sample_config.json   # Archivo de configuración de ejemplo.
│
├── build/                   # Archivos de compilación
│   ├── Makefile             # Archivo Make para compilar el proyecto.
│
└── README.md                # Instrucciones y detalles del proyecto.

```
