module.exports = {
  title: 'LoRaWAN Workshop',
  description: 'Introductie tot LoRaWAN aan de hand van een STEM workshop',
  themeConfig: {
    navbar: [
      {text: 'VIVES', link: 'https://www.vives.be'}
    ],
    repo: 'https://github.com/99-bugs/lorawan-twin-workshop',
    docsDir: 'docs',
    docsBranch: 'master',
    sidebar: [
      {
        text: 'De things',
        children: [
          {
            text: 'De SODAQ ExpLoRer',
            link: '/sodaq-explorer/'
          },
          {
            text: 'Datacaptatie',
            link: '/data-capture/'
          },




          {
            text: 'Grove sensoren',
            link: '/sensors/',
            children: [
              '/sensors/push_button/',
              '/sensors/switch/',
              '/sensors/q_touch/',
              '/sensors/rfid/',
              '/sensors/motion-sensor/',
              '/sensors/rotary-sensor/',
              '/sensors/tph-sensor/',
            ]
          }
        ]
      },
      {
        text: 'Het Internet',
        children: [
          {
            text: 'LoRaWAN',
            link: '/lorawan/',
          },
          {
            text: 'MQTT',
            link: '/mqtt/',
          }
        ]
      },
      // Visualuatie ?
      // Interactie ?
      // NodeRED + NodeRED dashboard + eventueel eigen dashboard ?


      // {
      //   title: 'De server',   // required
      //   collapsable: true, // optional, defaults to true
      //   sidebarDepth: 0,    // optional, defaults to 1
      //   children: [
      //     '/lamp/',
      //     '/mosquitto/',
      //     '/node-red/'
      //   ]
      // },
      // {
      //   title: 'Het dashboard',   // required
      //   path: '/iot-dashboard/',      // optional, which should be a absolute path.
      //   collapsable: true, // optional, defaults to true
      // },
    ],
  },
  serviceWorker: true,
  plugins: [],
}