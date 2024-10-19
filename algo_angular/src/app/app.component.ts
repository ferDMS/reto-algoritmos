import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterOutlet } from '@angular/router';
import { FormsModule } from '@angular/forms';
import { DomSanitizer, SafeHtml } from '@angular/platform-browser';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [RouterOutlet, CommonModule, FormsModule],
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'algo_angular';
  fileContents: string[] = ['', ''];
  searchPattern: string = '';
  autocompleteInput: string = '';
  autocompleteSuggestions: string[] = [];
  sanitizedContent: SafeHtml[] = [];

  constructor(private sanitizer: DomSanitizer) {}

  onFileSelected(event: Event, index: number): void {
    const input = event.target as HTMLInputElement;

    if (input?.files?.length) {
      const file: File = input.files[0];
      const reader = new FileReader();

      reader.onload = () => {
        const content = reader.result as string;
        this.fileContents[index] = content;
        this.sanitizedContent[index] = this.sanitizer.bypassSecurityTrustHtml(content);
      };

      reader.readAsText(file);
    }
  }

  buscar(): void {
    if (this.fileContents[0] && this.searchPattern) {
      const result1 = this.findPattern(this.fileContents[0], this.searchPattern);
      const intervals1 = JSON.parse(result1);
      this.fileContents[0] = this.highlightText(this.fileContents[0], intervals1);
    }

    if (this.fileContents[1] && this.searchPattern) {
      const result2 = this.findPattern(this.fileContents[1], this.searchPattern);
      const intervals2 = JSON.parse(result2);
      this.fileContents[1] = this.highlightText(this.fileContents[1], intervals2);
    }

    console.log(this.fileContents); // You can handle the result as needed
  }

  anterior(): void {
    // Acción para el botón "Anterior"
  }

  siguiente(): void {
    // Acción para el botón "Siguiente"
  }

  similitud(): void {
    if (this.fileContents[0] && this.fileContents[1]) {
      const result = this.findLCS(this.fileContents[0], this.fileContents[1]);
      console.log(result); // You can handle the result as needed
    }
  }

  palindromo(): void {
    if (this.fileContents[0]) {
      const result1 = this.findLongestPalindrome(this.fileContents[0]);
      const { start: start1, end: end1 } = JSON.parse(result1);
      const intervals1 = start1 !== undefined && end1 !== undefined ? [{ start: start1, end: end1 }] : [];
      this.fileContents[0] = this.highlightPalindrome(this.fileContents[0], intervals1);
    }

    if (this.fileContents[1]) {
      const result2 = this.findLongestPalindrome(this.fileContents[1]);
      const { start: start2, end: end2 } = JSON.parse(result2);
      const intervals2 = start2 !== undefined && end2 !== undefined ? [{ start: start2, end: end2 }] : [];
      this.fileContents[1] = this.highlightPalindrome(this.fileContents[1], intervals2);
    }

    console.log(this.fileContents); // You can handle the result as needed
  }

  autoCompletar(): void {
    if (this.fileContents[0] && this.autocompleteInput) {
      const result = this.autocomplete(this.fileContents[0], this.autocompleteInput);
      this.autocompleteSuggestions = JSON.parse(result);
    }
    console.log(this.autocompleteSuggestions)
  }

  highlightText(content: string, intervals: { start: number, end: number }[]): string {
    if (intervals.length === 0) {
      return content;
    }

    let highlightedContent = '';
    let lastIndex = 0;

    intervals.forEach(interval => {
      highlightedContent += content.substring(lastIndex, interval.start);
      highlightedContent += '<mark>' + content.substring(interval.start, interval.end + 1) + '</mark>';
      lastIndex = interval.end + 1;
    });

    highlightedContent += content.substring(lastIndex);
    return highlightedContent;
  }

  highlightPalindrome(content: string, intervals: { start: number, end: number }[]): string {
    if (intervals.length === 0) {
      return content;
    }

    let highlightedContent = '';
    let lastIndex = 0;

    intervals.forEach(interval => {
      highlightedContent += content.substring(lastIndex, interval.start);
      highlightedContent += '<mark class="palindrome">' + content.substring(interval.start, interval.end + 1) + '</mark>';
      lastIndex = interval.end + 1;
    });

    highlightedContent += content.substring(lastIndex);
    return highlightedContent;
  }


  zAlgo(text: string, pattern: string) {
    let combined = pattern + "$" + text;
    let len = combined.length;
    let Z = new Array(len).fill(0);

    let L = 0, R = 0;
    for (let i = 1; i < len; ++i) {
        if (i <= R) {
            Z[i] = Math.min(R - i + 1, Z[i - L]);
        }

        while (i + Z[i] < len && combined[Z[i]] === combined[i + Z[i]]) {
            Z[i]++;
        }

        if (i + Z[i] - 1 > R) {
            L = i;
            R = i + Z[i] - 1;
        }
    }

    let intervals = [];
    let lastEnd = -1;
    for (let i = pattern.length + 1; i < len; ++i) {
        if (Z[i] === pattern.length) {
            let start = i - pattern.length - 1;
            let end = start + pattern.length - 1;
            if (start > lastEnd) {
                intervals.push({ start, end });
                lastEnd = end;
            }
        }
    }

    return intervals;
  }

  findPattern(text: string, pattern: string) {
    // Execute the Z algorithm and get the found positions
    let result = this.zAlgo(text, pattern);

    // Build the JSON string manually
    let jsonOutput = "[\n";
    for (let i = 0; i < result.length; ++i) {
        jsonOutput += `    {"start": ${result[i].start}, "end": ${result[i].end}}`;
        if (i < result.length - 1) {
            jsonOutput += ",";
        }
        jsonOutput += "\n";
    }
    jsonOutput += "]";

    return jsonOutput;
  }

  preprocess(s: string): string {
    let t = "^";
    for (let c of s) {
      t += "#" + c;
    }
    t += "#$";
    return t;
  }

  toLowerCase(s: string): string {
    return s.toLowerCase();
  }

  manacherAlgo(s: string): { start: number, maxLen: number } {
    let t = this.preprocess(s);
    let m = t.length;
    let p = new Array(m).fill(0);

    let center = 0, right = 0;
    let maxLen = 0, start = 0;

    for (let i = 1; i < m - 1; ++i) {
      if (i < right) {
        let j = 2 * center - i;
        p[i] = Math.min(right - i, p[j]);
      }

      // Expand palindrome around center
      while (t[i + p[i] + 1] === t[i - p[i] - 1]) {
        p[i]++;
      }

      if (i + p[i] > right) {
        center = i;
        right = i + p[i];
      }

      if (p[i] > maxLen) {
        maxLen = p[i];
        start = (i - p[i] - 1) / 2; // Corrected calculation of start index
      }
    }

    return { start: Math.floor(start), maxLen };
  }

  findLongestPalindrome(text: string): string {
    // Convert text to lowercase
    text = this.toLowerCase(text);

    // Execute Manacher's algorithm
    let result = this.manacherAlgo(text);
    let start = result.start;
    let length = result.maxLen;
    let palindrome = text.substring(start, start + length);

    // Return result in JSON format
    return JSON.stringify({
      pal: palindrome,
      start: start,
      end: start + length - 1
    }, null, 2);
  }

  longestCommonSubstring(text1: string, text2: string): LCSResult {
    let n = text1.length;
    let m = text2.length;
    let dp = Array.from({ length: n + 1 }, () => Array(m + 1).fill(0));

    let maxLen = 0;
    let endIndex1 = 0;
    let endIndex2 = 0;

    for (let i = 1; i <= n; ++i) {
      for (let j = 1; i <= m; ++j) {
        if (text1[i - 1] === text2[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1] + 1;
          if (dp[i][j] > maxLen) {
            maxLen = dp[i][j];
            endIndex1 = i - 1;
            endIndex2 = j - 1;
          }
        }
      }
    }

    let startIndex1 = endIndex1 - maxLen + 1;
    let startIndex2 = endIndex2 - maxLen + 1;
    let lcs = text1.substring(startIndex1, startIndex1 + maxLen);

    return new LCSResult(lcs, startIndex1, endIndex1, startIndex2, endIndex2);
  }

  findLCS(text1: string, text2: string): string {
    let result = this.longestCommonSubstring(text1, text2);

    let output = [
      { text1: { start: result.start1, end: result.end1 } },
      { text2: { start: result.start2, end: result.end2 } }
    ];

    return JSON.stringify(output, null, 2);
  }

  autocomplete(content: string, prefix: string): string {
    let trie = new Trie();
    let uniqueWords = new Set<string>();
    let words = content.split(/\s+/);

    for (let word of words) {
      word = word.replace(/[^a-zA-Z0-9]/g, '').toLowerCase();
      if (word) {
        uniqueWords.add(word);
      }
    }

    for (let uniqueWord of uniqueWords) {
      trie.insert(uniqueWord);
    }

    let wordsWithPrefix = trie.getWordsWithPrefix(prefix);
    return JSON.stringify(wordsWithPrefix, null, 2);
  }
}

class LCSResult {
  lcs: string;
  start1: number;
  end1: number;
  start2: number;
  end2: number;

  constructor(lcs: string, start1: number, end1: number, start2: number, end2: number) {
    this.lcs = lcs;
    this.start1 = start1;
    this.end1 = end1;
    this.start2 = start2;
    this.end2 = end2;
  }
}

class TrieNode {
  children: { [key: string]: TrieNode };
  isEndOfWord: boolean;

  constructor() {
    this.children = {};
    this.isEndOfWord = false;
  }
}

class Trie {
  root: TrieNode;

  constructor() {
    this.root = new TrieNode();
  }

  insert(word: string): void {
    let node = this.root;
    for (let char of word) {
      if (!node.children[char]) {
        node.children[char] = new TrieNode();
      }
      node = node.children[char];
    }
    node.isEndOfWord = true;
  }

  search(word: string): boolean {
    let node = this.root;
    for (let char of word) {
      if (!node.children[char]) {
        return false;
      }
      node = node.children[char];
    }
    return node.isEndOfWord;
  }

  getWordsWithPrefix(prefix: string): string[] {
    let result: string[] = [];
    let node = this.root;
    for (let char of prefix) {
      if (!node.children[char]) {
        return result; // No words with the given prefix
      }
      node = node.children[char];
    }
    this.collectWords(node, prefix, result);
    return result;
  }

  collectWords(node: TrieNode, prefix: string, result: string[]): void {
    if (node.isEndOfWord) {
      result.push(prefix);
    }
    for (let char in node.children) {
      this.collectWords(node.children[char], prefix + char, result);
    }
  }
}