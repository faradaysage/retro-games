# Retro DOS Games Collection

A collection of DOS games and demos I developed in the late '90s and early 2000s, now playable in the browser using **JS-DOS**. This repository includes:

- **North of Nowhere** (Demo)
- **The Adventures of Something That Looks Like an Evil Troll** (Full Game)
- **Lt. Perry: Operation Keish** (Full Game)

Each game/demo is stored in `.jsdos` format for easy web-based play and has its original **source code** available in the `/src/` directory.

## 🎮 Play Online
You can play these games directly in your browser: **[https://faradaysage.github.io/retro-games/]**.

---

## 🕹 Games & Demos

### **North of Nowhere (Demo)**
- **Type:** 3D Demo
- **Development:** This was my **Major Qualifying Project (MQP)** at WPI, built in four months by a two-person team.
- **Technology:** Written entirely in **ANSI C and x86 assembly** with a **custom 3D engine**.
- **Features:**
  - Real-time generated landscapes.
  - Custom-built **graphics, animation, and physics engines**.
  - Effects like **lens distortions, water/jelly physics, and real-time lighting**.
  - **No third-party libraries** were used except for sound support.

---

### **The Adventures of Something That Looks Like an Evil Troll**
- **Type:** 2D Action-Adventure Game (Zelda-like)
- **Development:** Created in **one month** during Christmas break in my final year of university.
- **Technology:** Written in **C**, running in **DOS/Windows 95 (DOS4GW mode)**.
- **Features:**
  - A **large, interactive world**.
  - AI-driven **enemies, puzzles, and environmental interactions**.
  - **Handcrafted pixel art and level design**.
- **Controls:** See `/src/troll/readme.txt`

---

### **Lt. Perry: Operation Keish**
- **Type:** Space Shooter
- **Development:** My **first full game**, built at age 17.
- **Technology:** Written entirely in **C**, using **Mode 13h graphics**.
- **Features:**
  - Custom-built **sprite rendering and collision detection**.
  - **Sine wave-generated music** (no external sound files).
  - **Basic AI behaviors for enemies and boss fights**.
- **Controls:** See `/src/ltperry/readme.txt`

---

## 📜 Source Code
The original source code for each game is included in the `/src/` directory, along with **readme.txt** files that explain **controls and mechanics**.

- **`/src/nowhere/`** - Contains the 3D engine and rendering code.
- **`/src/troll/`** - Contains all game logic, AI, and graphics.
- **`/src/ltperry/`** - Early game development techniques and sprite-based rendering.

---

## 🛠 Running Locally
If you want to run these games outside the browser, you can:
1. Download **DOSBox**: [https://www.dosbox.com/download.php?main=1](https://www.dosbox.com/download.php?main=1)
2. Extract the game `.zip` file from `/games/`.
3. Open DOSBox, mount the game directory, and run the `.EXE` file.

---

## 📢 Contributing
This project is a **historical archive** of my early game development work. If you're interested in DOS game development, feel free to explore the source code!

---

## 📧 Contact
For any inquiries, reach out via **[Your Contact Info]**.

Enjoy the nostalgia! 🎮

