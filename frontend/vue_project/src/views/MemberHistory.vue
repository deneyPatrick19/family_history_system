<template>
  <div class="member-history">
    <h1>{{ member.name }} 的履历</h1>
    <div>
      <p><strong>出生日期:</strong> {{ member.dob }}</p>
      <p><strong>结婚日期:</strong> {{ member.marriageDate || '未记录' }}</p>
      <p><strong>死亡日期:</strong> {{ member.deathDate || '未记录' }}</p>
      <p><strong>生平简介:</strong> {{ member.bio || '未记录' }}</p>
    </div>
    <button @click="editHistory">编辑履历</button>
  </div>
</template>

<script>
export default {
  data() {
    return {
      member: {
        name: '张三',
        dob: '1980-01-01',
        marriageDate: '2005-06-15',
        deathDate: '',
        bio: '这是一个简短的生平简介。',
      }
    };
  },
  methods: {
    editHistory() {
      // 编辑履历逻辑，可以弹出一个编辑框
      alert('编辑履历');
    }
  }
};
</script>

<style scoped>
.member-history {
  max-width: 600px;
  margin: auto;
  text-align: left;
}

button {
  padding: 10px 20px;
  background-color: #4CAF50;
  color: white;
  border: none;
  cursor: pointer;
}
</style>
