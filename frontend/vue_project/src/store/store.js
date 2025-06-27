import { createStore } from 'vuex'

export default createStore({
  state: {
    // 存储用户信息
    user: {
      id: null,
      username: '',
      token: ''
    },
    // 存储家族成员信息
    members: [],
    // 存储选中的家族表ID（持久化）
    selectedFamilyTableId: localStorage.getItem('selectedFamilyTableId') || null
  },
  
  mutations: {
    // 设置用户信息
    SET_USER(state, user) {
      state.user = user
    },
    
    // 清除用户信息
    CLEAR_USER(state) {
      state.user = { id: null, username: '', token: '' }
    },
    
    // 添加家族成员
    ADD_MEMBER(state, member) {
      state.members.push(member)
    },
    
    // 设置家族成员列表
    SET_MEMBERS(state, members) {
      state.members = members
    },
    
    // 设置选中的家族表ID
    SET_SELECTED_FAMILY_TABLE_ID(state, familyTableId) {
      state.selectedFamilyTableId = familyTableId
      localStorage.setItem('selectedFamilyTableId', familyTableId)
    }
  },
  
  actions: {
    // 登录动作
    login({ commit }, userInfo) {
      commit('SET_USER', userInfo)
      // 同时保存到 localStorage
      localStorage.setItem('token', userInfo.token)
      localStorage.setItem('username', userInfo.username)
      if (userInfo.id) {
        localStorage.setItem('userId', userInfo.id)
      }
    },
    
    // 退出登录
    logout({ commit }) {
      commit('CLEAR_USER')
      commit('SET_SELECTED_FAMILY_TABLE_ID', null)
      localStorage.removeItem('token')
      localStorage.removeItem('username')
      localStorage.removeItem('userId')
      localStorage.removeItem('selectedFamilyTableId')
    },
    
    // 初始化用户信息（从 localStorage 读取）
    initUser({ commit }) {
      const token = localStorage.getItem('token')
      const username = localStorage.getItem('username')
      const userId = localStorage.getItem('userId')
      if (token && username) {
        commit('SET_USER', { 
          token, 
          username, 
          id: userId ? parseInt(userId) : null 
        })
      }
    },
    
    // 设置选中的家族表ID
    setSelectedFamilyTableId({ commit }, familyTableId) {
      commit('SET_SELECTED_FAMILY_TABLE_ID', familyTableId)
    }
  },
  
  getters: {
    // 获取用户信息
    user: state => state.user,
    
    // 判断是否已登录
    isLoggedIn: state => !!state.user.token,
    
    // 获取家族成员
    members: state => state.members,
    
    // 获取选中的家族表ID
    selectedFamilyTableId: state => state.selectedFamilyTableId
  }
})