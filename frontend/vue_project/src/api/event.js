import api from './familyTree'

// 事件相关API
export const eventAPI = {
  // 获取指定成员的所有事件
  getMemberEvents(memberId) {
    return api.get(`/event/member/${memberId}`)
  },

  // 添加事件
  addEvent(eventData) {
    return api.post('/event/insert', eventData)
  },

  // 更新事件
  updateEvent(eventData) {
    return api.post('/event/update', eventData)
  },

  // 删除事件
  deleteEvent(id) {
    return api.post('/event/delete', null, { params: { id } })
  },

  // 根据ID获取事件
  getEventById(id) {
    return api.post('/event/find', null, { params: { id } })
  },

  // 获取所有事件
  getAllEvents() {
    return api.get('/event/findall')
  }
} 