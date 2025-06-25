import { createStore } from 'vuex'

export default createStore({
  state: {
    // 存储用户信息
    user: {
      username: '',
      token: ''
    },
    // 存储家族成员信息
    members: []
  },
  
  mutations: {
    // 设置用户信息
    SET_USER(state, user) {
      state.user = user
    },
    
    // 清除用户信息
    CLEAR_USER(state) {
      state.user = { username: '', token: '' }
    },
    
    // 添加家族成员
    ADD_MEMBER(state, member) {
      state.members.push(member)
    },
    
    // 设置家族成员列表
    SET_MEMBERS(state, members) {
      state.members = members
    }
  },
  
  actions: {
    // 登录动作
    login({ commit }, userInfo) {
      commit('SET_USER', userInfo)
      // 同时保存到 localStorage
      localStorage.setItem('token', userInfo.token)
      localStorage.setItem('username', userInfo.username)
    },
    
    // 退出登录
    logout({ commit }) {
      commit('CLEAR_USER')
      localStorage.removeItem('token')
      localStorage.removeItem('username')
    },
    
    // 初始化用户信息（从 localStorage 读取）
    initUser({ commit }) {
      const token = localStorage.getItem('token')
      const username = localStorage.getItem('username')
      if (token && username) {
        commit('SET_USER', { token, username })
      }
    }
  },
  
  getters: {
    // 获取用户信息
    user: state => state.user,
    
    // 判断是否已登录
    isLoggedIn: state => !!state.user.token,
    
    // 获取家族成员
    members: state => state.members
  }
})