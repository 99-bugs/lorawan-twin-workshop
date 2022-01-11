module.exports = {
  title: 'LoRaWAN Workshop',
  description: 'Introductie tot LoRaWAN aan de hand van een STEM workshop',
  themeConfig: {
    navbar: [
      {text: 'VIVES', link: 'https://www.vives.be'}
    ],
    displayAllHeaders: false,
    sidebar: 'auto',
    repo: 'https://github.com/99-bugs/lorawan-twin-workshop',
    docsDir: 'docs',
    docsBranch: 'master',
    sidebar: [
      {
        title: 'De things',   // required
        collapsable: true, // optional, defaults to true
        sidebarDepth: 0,    // optional, defaults to 1
        children: [
          '/sodaq-explorer/',
          {
            title: 'Grove sensoren',   // required
            path: '/sensors/',      // optional, which should be a absolute path.
            collapsable: true, // optional, defaults to true
            sidebarDepth: 0,    // optional, defaults to 1
            children: [
              '/sensors/push_button/',
              '/sensors/switch/',
              '/sensors/q_touch/',
              '/sensors/rfid/',
              '/sensors/motion-sensor/',
              '/sensors/rotary-sensor/',
              '/sensors/tph-sensor/',
            ]
          },
        ]
      },
      {
        title: 'Het internet',   // required
        path: '/lorawan/',      // optional, which should be a absolute path.
        collapsable: true, // optional, defaults to true
      },
      {
        title: 'De server',   // required
        collapsable: true, // optional, defaults to true
        sidebarDepth: 0,    // optional, defaults to 1
        children: [
          '/lamp/',
          '/mosquitto/',
          '/node-red/'
        ]
      },
      {
        title: 'Het dashboard',   // required
        path: '/iot-dashboard/',      // optional, which should be a absolute path.
        collapsable: true, // optional, defaults to true
      },
    ],
  },
  serviceWorker: true,
  plugins: [],
}