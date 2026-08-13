package com.example.family_history_system.common.interceptor;

import com.example.family_history_system.common.response.Response;
import com.example.family_history_system.common.util.JwtUtil;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.springframework.stereotype.Component;
import org.springframework.web.servlet.HandlerInterceptor;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@Component
public class JwtInterceptor implements HandlerInterceptor {

    private static final String AUTH_HEADER = "Authorization";
    private static final String UNAUTHORIZED_MESSAGE = "未登录或token失效";

    private final ObjectMapper objectMapper = new ObjectMapper();

    private final JwtUtil jwtUtil;

    public JwtInterceptor(JwtUtil jwtUtil) {
        this.jwtUtil = jwtUtil;
    }

    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        // CORS 预检请求豁免
        if ("OPTIONS".equalsIgnoreCase(request.getMethod())) {
            return true;
        }

        String token = request.getHeader(AUTH_HEADER);

        // 无 token
        if (token == null || token.isEmpty()) {
            writeUnauthorized(response);
            return false;
        }

        // 校验 token
        try {
            if (!jwtUtil.validateToken(token)) {
                writeUnauthorized(response);
                return false;
            }
        } catch (Exception e) {
            // 任何异常（签名错误、过期、格式错误等）统一视为未授权
            writeUnauthorized(response);
            return false;
        }

        return true;
    }

    private void writeUnauthorized(HttpServletResponse response) throws Exception {
        response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
        response.setContentType("application/json;charset=UTF-8");
        response.getWriter().write(objectMapper.writeValueAsString(Response.buildFault(UNAUTHORIZED_MESSAGE)));
    }
}
