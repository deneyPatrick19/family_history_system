<template>
  <div class="welcome-container">
    <div class="welcome-header">
      <h1>欢迎使用家庭族谱管理系统</h1>
      <p>请选择您要使用的功能模块</p>
    </div>
    
    <div class="feature-grid">
      <div class="feature-card" @click="navigateTo('/personal-history')">
        <div class="card-icon">
          <el-icon size="40"><User /></el-icon>
        </div>
        <div class="card-content">
          <h3>个人信息</h3>
          <p>管理个人基本信息和生平履历</p>
        </div>
      </div>
      
      <div class="feature-card" @click="navigateTo('/family-table-manager')">
        <div class="card-icon">
          <el-icon size="40"><Files /></el-icon>
        </div>
        <div class="card-content">
          <h3>家谱表管理</h3>
          <p>创建、编辑和管理多个家谱表</p>
        </div>
      </div>
      
      <div class="feature-card" @click="navigateTo('/family-tree')">
        <div class="card-icon">
          <el-icon size="40"><Share /></el-icon>
        </div>
        <div class="card-content">
          <h3>家谱树</h3>
          <p>查看和编辑家族树形结构</p>
        </div>
      </div>
      
      <div class="feature-card" @click="navigateTo('/member-list')">
        <div class="card-icon">
          <el-icon size="40"><List /></el-icon>
        </div>
        <div class="card-content">
          <h3>成员列表</h3>
          <p>查看所有家族成员信息和事件</p>
        </div>
      </div>
    </div>
    
    <div class="welcome-footer">
      <p>当前用户：{{ username }}</p>
    </div>
  </div>
</template>

<script>
import { User, Files, Share, List } from '@element-plus/icons-vue'

export default {
  name: 'Welcome',
  components: {
    User,
    Files,
    Share,
    List
  },
  computed: {
    username() {
      return this.$store.getters.user.username || '未知用户'
    }
  },
  methods: {
    navigateTo(path) {
      this.$router.push(path)
    }
  }
}
</script>

<style scoped>
.welcome-container {
  padding: 40px;
  min-height: 100vh;
  background: #fff;
  display: flex;
  flex-direction: column;
  align-items: center;
}

.welcome-header {
  text-align: center;
  margin-bottom: 60px;
  color: #333;
}

.welcome-header h1 {
  font-size: 2.5rem;
  margin-bottom: 16px;
  font-weight: 600;
}

.welcome-header p {
  font-size: 1.2rem;
  color: #666;
}

.feature-grid {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(280px, 1fr));
  gap: 30px;
  max-width: 1200px;
  width: 100%;
  margin-bottom: 40px;
}

.feature-card {
  background: white;
  border-radius: 16px;
  padding: 30px;
  text-align: center;
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1);
  transition: all 0.3s ease;
  cursor: pointer;
  border: 1px solid #e4e7ed;
}

.feature-card:hover {
  transform: translateY(-4px);
  box-shadow: 0 8px 24px rgba(0, 0, 0, 0.15);
  border-color: #42ade7;
}

.card-icon {
  margin-bottom: 20px;
  color: #42ade7;
}

.card-content h3 {
  font-size: 1.5rem;
  margin-bottom: 12px;
  color: #333;
  font-weight: 600;
}

.card-content p {
  color: #666;
  line-height: 1.6;
  margin: 0;
}

.welcome-footer {
  text-align: center;
  color: #666;
  margin-top: auto;
}

.welcome-footer p {
  font-size: 1rem;
}

@media (max-width: 768px) {
  .welcome-container {
    padding: 20px;
  }
  
  .welcome-header h1 {
    font-size: 2rem;
  }
  
  .feature-grid {
    grid-template-columns: 1fr;
    gap: 20px;
  }
  
  .feature-card {
    padding: 20px;
  }
}
</style>