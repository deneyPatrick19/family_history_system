import api from './familyTree'

// 家族表相关API
export const familyTableAPI = {
  // 获取用户的所有家族表
  getUserFamilyTables(userId) {
    return api.get(`/family-table/user/${userId}`)
  },

  // 创建新的家族表
  createFamilyTable(tableData) {
    return api.post('/family-table/create', tableData)
  },

  // 获取所有家族表
  getAllFamilyTables() {
    return api.get('/family-table/findall')
  },

  // 根据ID获取家族表
  getFamilyTableById(id) {
    return api.post('/family-table/find', { id })
  },

  // 更新家族表
  updateFamilyTable(tableData) {
    return api.post('/family-table/update-family-table', tableData)
  },

  // 删除家族表
  deleteFamilyTable(id) {
    return api.post('/family-table/delete-family-table', { id })
  }
} 