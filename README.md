# 🎮 UE5 Showcase – Unreal Engine 5 (UE5)

An Unreal Engine 5 sandbox for testing and demonstrating gameplay systems, with a focus on modular weapon mechanics, character animation fidelity, and usage of the Gameplay Ability System. This solo project highlights a clean, scalable architecture for prototyping shooter mechanics and animation features in a high-fidelity third-person context.

> ⚠️ **Work in Progress:** This project is currently in development. New features, visuals, and polish are still being added.  
>
> 🎨 This is a solo project — all design, programming, and visual effects were done without an artist. The project's appearance is driven entirely by custom shaders, code-based visuals, and gameplay-driven ideas.

---

## 🧠 Key Features

- 🔫 **Weapon System with Equip Slots**
  - Players can equip and switch between different weapons.
  - Each weapon uses modular logic for damage, firing, and abilities.

- 🦶 **Inverse Kinematics (IK)**
  - IK-based foot placement system ensures feet align naturally with the ground.
  - Adds realism when navigating slopes, stairs, and uneven terrain.

- 🎭 **Animation Retargeting (Mixamo to UE5 Skeletons)**
  - Imported and retargeted Mixamo animations to UE skeletons.
  - Enabled smooth, responsive character movement without custom motion capture.

- 💥 **Gameplay Ability System (GAS) Integration**
  - Implemented Unreal’s GAS for:
    - Health and damage
    - Damage over time (DOT)
    - Extendable future abilities
  - Cleanly separates logic into reusable abilities and effects.

---

## 🔧 Tech Stack

- **Engine**: Unreal Engine 5
- **Languages**: C++, Blueprint
- **Systems Used**: Gameplay Ability System (GAS), IK Rig, Retarget Manager
- **Tools**: Visual Studio, Unreal Editor

---
