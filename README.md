# 🎮 FireBase_RealTime – Unreal Engine Firebase Leaderboard

This project demonstrates a **custom leaderboard system in Unreal Engine 5** powered by **Firebase Realtime Database**.  
It showcases my ability to integrate **C++ game logic, REST API communication, and UI widgets** to create a working online system.

---

## 🚀 Project Overview
- 🔗 Connected **Unreal Engine 5** with **Firebase Realtime Database** using REST API.  
- 🏆 Implemented a **Leaderboard System** (Increase Score, Save Score, Load Leaderboard).  
- 🖼️ Created a **UMG Widget** to display scores dynamically in-game.  
- 📡 Supports multiple players with unique IDs and cloud-synced scores.  

This project can be reused as a **template** for any multiplayer or single-player game requiring an online leaderboard.

---

## 🛠️ Tech Stack
- **Unreal Engine 5** (C++ + Blueprints)  
- **Firebase Realtime Database** (REST API Integration)  
- **UMG Widgets** for leaderboard UI  
- **HTTP Module in UE5** for API calls  

---

## 📌 How It Works
1. **Increase Score** → Adds points to a player.  
2. **Save Score** → Pushes player score to Firebase.  
3. **Load Leaderboard** → Fetches and displays scores inside a widget.  

### Blueprint Example:
- `IncreaseScore(PlayerID, Amount)`
- `SaveScore(PlayerID, Score)`
- `LoadLeaderboard()`

---

## 🖼️ Preview
*(Add screenshots here – e.g., Blueprint nodes, leaderboard widget in-game UI)*  

---

## ⚡ Setup
1. Clone the repo:
   ```bash
   git clone https://github.com/AjayvirJangid/FireBase_RealTime.git
