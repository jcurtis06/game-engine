//
// Created by 06jcu on 8/14/2023.
//

#pragma once

#include "raylib.h"

struct Animation {
    explicit Animation(const Texture2D& texture,
                       int h_frames, int v_frames,
                       int start_frame, int end_frame,
                       float frame_duration) :
        texture(texture),
        h_frames(h_frames),
        v_frames(v_frames),
        start_frame(start_frame),
        end_frame(end_frame),
        frame_duration(frame_duration) {
        current_frame = start_frame;
    }

    int h_frames, v_frames;
    int start_frame, end_frame;
    int current_frame;
    float frame_duration;

    Texture2D texture;

    void render(Color tint = WHITE, const Vector2& position = {0, 0}) {
        _frame_timer += GetFrameTime();

        if (_frame_timer >= frame_duration) {
            current_frame++;
            _frame_timer = 0;
        }

        if (current_frame > end_frame) {
            current_frame = start_frame;
        }

        int x = current_frame % h_frames;
        int y = current_frame / h_frames;

        Rectangle source{
            (float)(texture.width / h_frames * x),
            (float)(texture.height / v_frames * y),
            (float)(texture.width / h_frames),
            (float)(texture.height / v_frames)
        };

        DrawTextureRec(texture, source, position, tint);
    }
private:
    float _frame_timer = 0;
};
