wig20 = load('C:\Users\jakub\Desktop\Pliki studia\sem4\Metody Numeryczne\Projekt1\Projekt1\Wig20Otwarcie.txt');
figure;
plot(wig20);
legend('Wig20');
xlabel('Time');
ylabel('Value');
title('Wig20');

wig20200 = wig20(1:200);
figure;
plot(wig20200);
legend('Wig20');
xlabel('Time');
ylabel('Value');
title('Wig20');

signal  = load('C:\Users\jakub\Desktop\Pliki studia\sem4\Metody Numeryczne\Projekt1\Projekt1\WynikiSignal.txt');
macd = load('C:\Users\jakub\Desktop\Pliki studia\sem4\Metody Numeryczne\Projekt1\Projekt1\WynikiMacd.txt');
figure;
hold on;
plot(signal);
plot(macd);
legend('Signal', 'MACD');
xlabel('Time');
ylabel('Value');
title('Signal and MACD');
hold off;

macd200 = macd(1:200);
signal200 = signal(1:200);
figure;
hold on;
plot(signal200);
plot(macd200);
legend('Signal', 'MACD');
xlabel('Time');
ylabel('Value');
title('Signal and MACD');
hold off;