#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>

using namespace geode::prelude;

// Simple preview autoplay.
// This is intended for the editor preview/playtest.
// It taps jump repeatedly while the preview is running.
// It is not a level solver.
class $modify(PreviewAutoPlay, LevelEditorLayer) {
protected:
    struct Fields {
        bool active = false;
        bool pressed = false;
        float timer = 0.f;
    };

    void stopAutoPlay() {
        if (m_fields->pressed) {
            this->releaseButton(1, false);
            m_fields->pressed = false;
        }
        m_fields->active = false;
        m_fields->timer = 0.f;
    }

    void onPlaytest() {
        LevelEditorLayer::onPlaytest();

        m_fields->active = true;
        m_fields->pressed = false;
        m_fields->timer = 0.f;
    }

    void onPausePlaytest() {
        if (m_fields->pressed) {
            this->releaseButton(1, false);
            m_fields->pressed = false;
        }
        m_fields->active = false;
        LevelEditorLayer::onPausePlaytest();
    }

    void onResumePlaytest() {
        LevelEditorLayer::onResumePlaytest();

        m_fields->active = true;
        m_fields->pressed = false;
        m_fields->timer = 0.f;
    }

    void onStopPlaytest() {
        if (m_fields->pressed) {
            this->releaseButton(1, false);
            m_fields->pressed = false;
        }
        m_fields->active = false;
        m_fields->timer = 0.f;

        LevelEditorLayer::onStopPlaytest();
    }

    void update(float dt) {
        LevelEditorLayer::update(dt);

        if (!m_fields->active) {
            return;
        }

        m_fields->timer += dt;

        if (!m_fields->pressed && m_fields->timer >= 0.16f) {
            this->pushButton(1, false);
            m_fields->pressed = true;
            m_fields->timer = 0.f;
            return;
        }

        if (m_fields->pressed && m_fields->timer >= 0.05f) {
            this->releaseButton(1, false);
            m_fields->pressed = false;
            m_fields->timer = 0.f;
        }
    }
};