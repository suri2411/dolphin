// Copyright 2026 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "VideoCommon/RommMenuUI.h"

#include <array>

#include <imgui.h>

#include "Common/Config/Config.h"
#include "Core/Config/MainSettings.h"

std::unique_ptr<RommMenuUI> g_romm_menu_ui;

namespace
{
// Mittig und schmal: am Fernseher wird aus zwei Metern gelesen, und der
// Rand eines Bildschirms ist dort oft abgeschnitten.
constexpr float FENSTER_BREITE = 260.0f;
constexpr std::array<const char*, 4> EINTRAEGE = {
    "Leiser",
    "Lauter",
    "Ton aus / an",
    "Spiel beenden",
};
}  // namespace

void RommMenuUI::Hoch()
{
  const int anzahl = static_cast<int>(Eintrag::Anzahl);
  // Umlaufend: mit vier Eintraegen ist der Weg nach oben zum letzten kuerzer
  // als dreimal nach unten.
  m_index = (m_index + anzahl - 1) % anzahl;
}

void RommMenuUI::Runter()
{
  m_index = (m_index + 1) % static_cast<int>(Eintrag::Anzahl);
}

void RommMenuUI::Display()
{
  if (!m_offen)
    return;

  const float scale = ImGui::GetIO().DisplayFramebufferScale.x;
  const ImVec2 bild = ImGui::GetIO().DisplaySize;
  const float breite = FENSTER_BREITE * scale;

  ImGui::SetNextWindowPos(ImVec2((bild.x - breite) * 0.5f, bild.y * 0.25f),
                          ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(breite, 0.0f), ImGuiCond_Always);
  ImGui::SetNextWindowBgAlpha(0.9f);

  if (!ImGui::Begin("RomM Arcade", nullptr,
                    ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings |
                        ImGuiWindowFlags_NoFocusOnAppearing))
  {
    ImGui::End();
    return;
  }

  // Der Wert gehoert dazu: "Leiser" ohne Zahl sagt nicht, ob man am Anschlag
  // ist oder ob die Taste gar nicht ankommt.
  const int lautstaerke = Config::Get(Config::MAIN_AUDIO_VOLUME);
  const bool stumm = Config::Get(Config::MAIN_AUDIO_MUTED);
  ImGui::Text("Lautstärke: %d %%%s", lautstaerke, stumm ? "  (stumm)" : "");
  ImGui::Separator();

  for (int i = 0; i < static_cast<int>(Eintrag::Anzahl); ++i)
  {
    const bool gewaehlt = (i == m_index);
    // Selectable statt Text: ImGui hebt die Auswahl dann selbst hervor, in
    // den Farben des laufenden Stils.
    ImGui::Selectable(EINTRAEGE[i], gewaehlt);
  }

  ImGui::Separator();
  ImGui::TextDisabled("A wählt · B oder Guide schließt");
  ImGui::End();
}
