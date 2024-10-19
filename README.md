# Reto Algoritmos

## Descripción

El entregable consiste en una aplicación web para el procesamiento de archivos de texto plano. La aplicación permite realizar varias operaciones sobre los textos cargados, utilizando algoritmos específicos implementados desde cero. Las funcionalidades incluyen búsqueda de patrones, similitud entre textos, detección de palíndromos y auto-completado.

## Funcionalidades

- Buscar: Busca un patrón en un texto y resaltar en amarillo. Utiliza el algoritmo Z.
- Similitud: Encuentra la subcadena común más larga entre ambos textos y la resalta en color azul. Utiliza el algoritmo LCS.
- Palíndromo: Busca el palíndromo más grande en el texto1 y lo resalta en color verde. Utiliza el algoritmo Manacher.
- Auto-Completar: Muestra una lista desplegable de opciones para auto-completar. Utiliza la estructura de datos Tries.

## Código

`src/algos/`: Contiene las implementaciones de los algoritmos en C++. El equivalente a estos algoritmos fueron implementados como funciones en Typescript para facilitar la implementación de la solución.

`app.component.ts`: Componente principal de la aplicación que maneja toda la lógica. Aquí adentro es donde se definieron los equivalentes de las funciones de C++.

`styles.css`: Donde se definen los estilos del remarcado

## Instalación

Clonar el repo

```
git clone https://github.com/ferDMS/reto-algoritmos
cd algo_angular
```

Instalar dependencias

```
npm install
```

Ejecutar la aplicación

```
npm start
```

## Manual

1. Utilice el botón `Choose file` para seleccionar uno o dos archivos de texto plano (.txt). Al cargar los archivos se habilitan las opciones.

2. Ingrese el patrón a buscar en el campo de texto correspondiente. Haga clic en el botón `Buscar` para encontrar y resaltar todas las apariciones del patrón en color amarillo.

3. Haga clic en el botón `SIM` para encontrar la subcadena común más larga entre los dos textos cargados y resaltarla en color azul.

4. Haga clic en el botón `Palíndromo` para encontrar el palíndromo más largo en el texto cargado y resaltarlo en color verde.

5. Escriba en el campo de texto de `Autocomplete` para ver las opciones de auto-completado basadas en el contenido del texto cargado.

## Aportes

### Fer Monroy

- Implementar Z, Manacher y LCS
- Funciones de resaltado (back)
- Manual de usuario

### Fer Tenchipe

- Implementar Tries
- Moverle al framework de JS
- Aplicar resaltado de texto (front)
- Diseño de app
