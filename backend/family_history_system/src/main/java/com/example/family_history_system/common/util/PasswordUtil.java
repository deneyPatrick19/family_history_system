package com.example.family_history_system.common.util;

import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;

public class PasswordUtil {
    private static final BCryptPasswordEncoder ENCODER = new BCryptPasswordEncoder(7);

    public static String encode(String raw) {
        return ENCODER.encode(raw);
    }

    public static boolean matches(String raw, String hash) {
        if (raw == null || hash == null) return false;
        return ENCODER.matches(raw, hash);
    }
}
