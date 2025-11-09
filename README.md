# Project 3 MP3 tag reader for ID3 V2

A command-line MP3 Tag Reader and Editor built in C.
It allows users to view and modify ID3v2 tags (like title, artist, album, year, genre, and comment) from .mp3 files directly from the terminal.

---
## ✨ Features
- 🔍 View MP3 Metadata – Display ID3v2 tag details such as Title, Artist, Album, Year, Genre, and Comment.
- ✏️ Edit Tags – Modify specific tags using simple command-line options (-t, -a, -A, -y, -g, -c).
- 🧠 Argument Validation – Validates all command-line inputs for file presence and proper formats.
- 🗂️ File Handling – Opens, reads, and updates MP3 files safely in binary mode.
- ⚙️ ID3v2 Compliance – Reads and updates tag frames according to the ID3v2 standard structure.
- 💾 Non-Destructive Editing – Creates a duplicate edited file before replacing the original, preserving data integrity.
- 🧱 Modular Design – Code is organized into multiple files for better readability and maintenance.
- 🚨 Error Detection – Detects invalid arguments, unsupported operations, or file issues.
- 💡 User-Friendly Help – Includes a built-in help menu explaining all available options.

---
# 🧮 How It Works
🧮 How It Works
- Reads the .mp3 file’s ID3v2 tag section.
- Displays or modifies the specific tag frame (e.g., TIT2, TPE1, TALB, TYER, TCON, COMM).
- During editing:
  Copies the original file to a temporary duplicate.
  Rewrites the tag with the new value.
  Renames the duplicate to the original filename while keeping a backup.
- For viewing, extracts and prints tag data in a clean format.

# 📂 Project Structure
├── main.c          # Entry point; handles mode selection (view/edit/help)
├── operations.c    # Core logic for tag reading, editing, and validation
├── operations.h    # Function declarations and structure definitions
├── types.h         # User-defined enums and status types
└── sample.mp3      # Example file for testing
