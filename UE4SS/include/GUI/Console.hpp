#pragma once

#include <mutex>
#include <string>
#include <vector>

#include <DynamicOutput/OutputDevice.hpp>
#include <TextEditor.h>
#include <imgui.h>

using namespace RC;

namespace RC::GUI
{
    class Console
    {
      private:
        char m_input_buffer[256]{};
        std::vector<std::string> m_lines{};
        ImGuiTextFilter m_filter{};
        float m_previous_max_scroll_y{};
        float m_current_console_output_width{};
        std::mutex m_lines_mutex{};
        TextEditor m_text_editor{};
        TextEditor m_repl_text_editor{};
        float m_console_size = -210;
        float m_repl_size = 150;
        TextEditor::Breakpoints m_breakpoints{};
        const size_t m_maximum_num_lines{50000};

      public:
        Console()
        {
            m_text_editor.SetConsoleMode(true);
            m_text_editor.SetColorizerEnable(false);
            m_text_editor.SetLanguageDefinition(GetLanguageDefinitionNone());
            m_text_editor.SetPalette(GetPalette());
            m_text_editor.SetBreakpoints(m_breakpoints);
            m_text_editor.SetTextFilter(&m_filter);

            m_repl_text_editor.SetConsoleMode(false);
            m_repl_text_editor.SetColorizerEnable(true);
            m_repl_text_editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
            m_repl_text_editor.SetPalette(GetPalette());
            m_repl_text_editor.SetShowWhitespaces(false);
            m_repl_text_editor.SetText("");
        }

      private:
        auto GetLanguageDefinitionNone() -> const TextEditor::LanguageDefinition&;
        auto GetPalette() const -> const TextEditor::Palette&;

      public:
        auto render() -> void;
        auto render_search_box() -> void;
        auto render_repl_editor() -> void;
        auto flush_repl_script() -> std::string;
        auto add_line(const std::string&, Color::Color) -> void;
        auto add_line(const std::wstring&, Color::Color) -> void;
    };
} // namespace RC::GUI
