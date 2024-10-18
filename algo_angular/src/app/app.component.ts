import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterOutlet } from '@angular/router';
import { FormsModule } from '@angular/forms'; // Importa FormsModule

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [RouterOutlet, CommonModule, FormsModule], // Añade FormsModule aquí
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'algo_angular';
  fileContents: string[] = ['', '']; // Inicializar con dos espacios para los archivos
  searchPattern: string = '';
  autocompleteInput: string = '';
  autocompleteSuggestions: string[] = [];

  // Método que se ejecuta cuando el usuario selecciona un archivo
  onFileSelected(event: Event, index: number): void {
    const input = event.target as HTMLInputElement;

    if (input?.files?.length) {
      const file: File = input.files[0];
      const reader = new FileReader();

      reader.onload = () => {
        const content = reader.result as string;
        this.fileContents[index] = this.highlightText(content, 10, 20); // Ejemplo de índices
      };

      reader.readAsText(file);
    }
  }

  // Métodos para los botones
  buscar(): void {
    // Acción para el botón "Buscar"
  }

  anterior(): void {
    // Acción para el botón "Anterior"
  }

  siguiente(): void {
    // Acción para el botón "Siguiente"
  }

  similitud(): void {
    // Acción para el botón "Similitud"
  }

  palindromo(): void {
    // Acción para el botón "Palíndromo"
  }

  autoCompletar(): void {
    // Acción para el campo de texto "Auto-Completar"
  }

  // Método de ejemplo para resaltar texto
  highlightText(content: string, start: number, end: number): string {
    return content.substring(0, start) + '<mark>' + content.substring(start, end) + '</mark>' + content.substring(end);
  }
}