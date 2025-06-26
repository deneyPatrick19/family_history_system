import axios from 'axios'

// 创建axios实例
const api = axios.create({
  baseURL: 'http://localhost:8080',
  timeout: 10000,
  headers: {
    'Content-Type': 'application/json'
  }
})

// 请求拦截器
api.interceptors.request.use(
  config => {
    // 可以在这里添加token等认证信息
    const token = localStorage.getItem('token')
    if (token) {
      config.headers.Authorization = `Bearer ${token}`
    }
    return config
  },
  error => {
    return Promise.reject(error)
  }
)

// 响应拦截器
api.interceptors.response.use(
  response => {
    return response
  },
  error => {
    console.error('API请求错误:', error)
    return Promise.reject(error)
  }
)

// 家谱树相关API
export const familyTreeAPI = {
  // 获取家谱树数据
  getFamilyTree(familyTableId) {
    return api.get(`/family-tree/${familyTableId}`)
  },

  // 保存节点
  saveNode(nodeData) {
    return api.post('/family-tree/save-node', nodeData)
  },

  // 更新节点
  updateNode(nodeData) {
    return api.post('/family-tree/update-node', nodeData)
  },

  // 删除节点
  deleteNode(nodeData) {
    return api.post('/family-tree/delete-node', nodeData)
  }
}

export default api 