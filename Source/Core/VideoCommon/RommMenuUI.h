// Copyright 2026 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <memory>

// RomM Arcade: ein kleines Menue auf der Guide-Taste des Pads.
//
// Am Fernseher gibt es keine Tastatur und keine Maus. Lautstaerke und
// Beenden waren damit nur ueber Dolphins Menueleiste erreichbar - also gar
// nicht. Dieses Menue liegt ueber dem Bild und wird allein mit dem Pad
// bedient.
//
// Bewusst ohne Qt: gezeichnet wird mit ImGui im Videofaden, wie der
// Netplay-Chat. Was beim Bestaetigen geschehen soll, entscheidet der
// HotkeyScheduler - der kennt Lautstaerke und Beenden bereits, und
// VideoCommon soll nichts davon wissen muessen.
class RommMenuUI
{
public:
  enum class Eintrag : int
  {
    Leiser = 0,
    Lauter,
    Stumm,
    Beenden,
    Anzahl,
  };

  void Display();

  bool IstOffen() const { return m_offen; }
  void Umschalten() { m_offen = !m_offen; }
  void Schliessen() { m_offen = false; }

  void Hoch();
  void Runter();
  Eintrag Gewaehlt() const { return static_cast<Eintrag>(m_index); }

private:
  bool m_offen = false;
  int m_index = 0;
};

extern std::unique_ptr<RommMenuUI> g_romm_menu_ui;
