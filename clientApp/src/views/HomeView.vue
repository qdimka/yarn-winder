<script lang="ts">
import LvInput from 'lightvue/input';
import LvButton from 'lightvue/button';
import LvCard from 'lightvue/card';
import {useCounterStore} from "@/stores/counter";
import {computed} from "vue";
import {storeToRefs} from "pinia";

export default {
  setup(props, ctx) {
    const counter = useCounterStore();
    const {started, count} = storeToRefs(counter);
    return {
      count, started, counter
    }
  },
  methods: {
    async getStatus() {
      const result = await fetch("/status", {
        method: "GET",
        headers: {
          "Content-Type": "application/json",
        },
      })

      const response = (await result.json()) as any;

      this.counter.updateVal(response.stepperRevolutionsCount)
      this.counter.updateStarted(response.started)
    },
    async start() {
      await fetch("/move", {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({
          count: this.count,
        })
      });
      this.counter.start()
    },
    async stop() {
      await fetch("/reboot", {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        }
      });
      this.counter.stop()
    },
  },
  components: {
    LvInput,
    LvButton,
    LvCard
  },
  created() {
    this.getStatus();
  }
};
</script>

<template>
  <div class="session" v-if="!started">
    <div class="content">
      <div class="session-input">
        <lv-input type="number"
                  v-model="count"
                  label="Количество оборотов"
                  placeholder="Введите целое число"
                  :bottom-bar="true"/>
      </div>
    </div>
    <lv-button @click="start" class="start-btn" label="Запуск" type="button" size="l" />
  </div>

  <div class="session" v-if="started">
    <LvCard
        :shadowStyle="1"
        padding="20px"
        borderRadius="4px"
        backgroundColor="#DBE8EB"
    >
      <lv-button @click="stop" class="start-btn" label="Остановить" type="button" size="l" />
    </LvCard>
  </div>
</template>


<style scoped>
.session > .content {
  display: flex;
  flex-direction: column;
  row-gap: 24px;
}

.session > .start-btn {
  margin-top: 32px;
  width: 100%;
}
</style>